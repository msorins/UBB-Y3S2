package com.mircea.sorin.sebastian.officeairquality

import android.app.Activity
import android.os.Bundle
import android.util.Log
import com.google.android.things.pio.PeripheralManager
import com.google.android.things.pio.UartDevice
import java.io.IOException
import android.system.Os.listen
import com.google.firebase.firestore.DocumentReference
import com.google.firebase.firestore.FirebaseFirestore
import com.koushikdutta.async.http.server.AsyncHttpServerResponse
import com.koushikdutta.async.http.server.AsyncHttpServerRequest
import com.koushikdutta.async.http.server.HttpServerRequestCallback
import com.koushikdutta.async.http.WebSocket
import com.koushikdutta.async.http.server.AsyncHttpServer
import java.lang.Exception
import java.sql.Timestamp
import java.time.Instant
import kotlin.concurrent.fixedRateTimer


/**
 * Skeleton of an Android Things activity.
 *
 * Android Things peripheral APIs are accessible through the class
 * PeripheralManagerService. For example, the snippet below will open a GPIO pin and
 * set it to HIGH:
 *
 * <pre>{@code
 * val service = PeripheralManagerService()
 * val mLedGpio = service.openGpio("BCM6")
 * mLedGpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW)
 * mLedGpio.value = true
 * }</pre>
 * <p>
 * For more complex peripherals, look for an existing user-space driver, or implement one if none
 * is available.
 *
 * @see <a href="https://github.com/androidthings/contrib-drivers#readme">https://github.com/androidthings/contrib-drivers#readme</a>
 *
 */

data class Reading(val timestamp: Long, val humidity: Float, val temperature: Float, val co: Float) {
}

class MainActivity : Activity() {
    // UART Device Name
    private lateinit var UART_DEVICE_NAME: String
    private var mDevice: UartDevice? = null

    private var humidity: Float = 0.0f
    private var temperature: Float = 0.0f
    private var co: Float = 0.0f

    lateinit var db: FirebaseFirestore
    var EVERY_SECOND = 5000L

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    override fun onStart() {
        super.onStart()
        Log.d("START", "I'm started")

        // Initialise FirebaseFirestore
        db = FirebaseFirestore.getInstance()

        // Get PeripheralManager instance
        val manager = PeripheralManager.getInstance()

        // Get uart device list
        val deviceList: List<String> = manager.uartDeviceList

        // Check if any devices found
        if (deviceList.isEmpty()) {
            Log.i("NOUART", "No UART port available on this device.")
        } else {
            Log.i("YEUART", "List of available devices: $deviceList")

            // Set the uart device name to the last usb one
            deviceList.forEach { device -> if (device.toLowerCase().contains("usb")) UART_DEVICE_NAME = device }
        }

        // Check if any usb device was found
        if (!::UART_DEVICE_NAME.isInitialized) {
            finish()
            System.exit(0)
            return
        }

        // Attempt to access the UART device
        mDevice = try {
            PeripheralManager.getInstance()
                .openUartDevice(UART_DEVICE_NAME)
        } catch (e: IOException) {
            Log.w("UARTFAIL", "Unable to access UART device", e)
            null
        }

        if (mDevice == null) {
            finish()
            System.exit(0)
            return
        }

        Log.d("USBCONN", "Connected to usb")

        // Configure usb device
        configureUartFrame(mDevice!!)

        // Start the server
        Thread {
            val server = AsyncHttpServer()
            server.get(
                "/humidity"
            ) { request, response -> run {
                response.getHeaders().set("Access-Control-Allow-Methods", "POST, GET, DELETE, PUT, OPTIONS");
                response.getHeaders().set("Access-Control-Allow-Origin", "*");
                response.send(this.humidity.toString())
            } }

            server.get(
                "/temperature"
            ) { request, response -> run {
                response.getHeaders().set("Access-Control-Allow-Methods", "POST, GET, DELETE, PUT, OPTIONS");
                response.getHeaders().set("Access-Control-Allow-Origin", "*");
                response.send(this.temperature.toString())
            }}

            server.get(
                "/co"
            ) { request, response -> run {
                response.getHeaders().set("Access-Control-Allow-Methods", "POST, GET, DELETE, PUT, OPTIONS");
                response.getHeaders().set("Access-Control-Allow-Origin", "*");
                response.send(this.co.toString())
              }
            }
            server.listen(5000)
        }.run()

        // Send data to Firestore every x seconds
        fixedRateTimer("default", false, 0L, EVERY_SECOND){
            val readingsCollectionRef = db.collection("readings")
            val reading = Reading(timestamp = System.currentTimeMillis(),
                humidity = this@MainActivity.humidity,
                temperature = this@MainActivity.temperature,
                co = this@MainActivity.co)

            readingsCollectionRef.add(reading)
        }

        // Listen for serial
        readUartBuffer(mDevice!!)
    }


    @Throws(IOException::class)
    fun readUartBuffer(uart: UartDevice) {
        // Maximum amount of data to read at one time
        val maxCount = 204800

        uart.apply {
            ByteArray(maxCount).also { buffer ->
                var count: Int = read(buffer, buffer.size)
                while (count >= 0) {
                    Log.d("BlaBla", "Read $count bytes from peripheral")
                    count = read(buffer, buffer.size)


                    var msg = String(buffer)
                    processArduinoOutput(msg)
                }
            }
        }
    }
    override fun onDestroy() {
        super.onDestroy()

        try {
            mDevice?.close()
            mDevice = null
        } catch (e: IOException) {
            Log.w("UARTFAIL", "Unable to close UART device", e)
        }

        // TODO maybe stop sock server?

        Log.d("STOPP", "I'm stopped")
    }


    @Throws(IOException::class)
    fun configureUartFrame(uart: UartDevice) {
        uart.apply {
            // Configure the UART port
            setBaudrate(9600)
//            setDataSize(8)
//            setParity(UartDevice.PARITY_NONE)
//            setStopBits(1)
        }
    }

    fun processArduinoOutput(originalValue: String) {
        // Delete new lines
        var valueTrimmed = originalValue.replace("\r", "").replace("\n", "")

        // Split into more values
        var readings = valueTrimmed.split("#")

        // Go through all the distinctive readings
        for(reading in readings) {

            var parts = reading.split(";")
            for(splitEntity in parts) {
                var splitedEntity = splitEntity.split(" ")
                if(splitedEntity.size != 2) {
                    continue
                }
                var name = splitedEntity[0]
                var fval = splitedEntity[1]
                try {
                    if(name == "CO") {
                        this.co = fval.toFloat()
                    }
                    if(name == "Temperature") {
                        this.temperature = fval.toFloat()
                    }
                    if(name == "Humidity") {
                        this.humidity = fval.toFloat()
                    }
                }catch(ex: Exception) {

                }

            }
        }

    }

}