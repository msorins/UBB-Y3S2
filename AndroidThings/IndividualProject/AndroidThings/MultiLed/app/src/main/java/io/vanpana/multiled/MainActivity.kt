package io.vanpana.multiled

import android.app.Activity
import android.os.Bundle
import android.util.Log
import com.google.android.things.pio.PeripheralManager
import com.google.android.things.pio.UartDevice
import java.io.IOException

class MainActivity : Activity() {
    // UART Device Name
    private lateinit var UART_DEVICE_NAME: String
    private var mDevice: UartDevice? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    override fun onStart() {
        super.onStart()
        Log.d("START", "I'm started")

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

        // Build the socket server
        val socketServer = SocketServer()

        // Listen for clients and colors changes
        socketServer.run(object : LedColorChanged {
            override fun colorChanged(colorString: String) {
                sendDataToDevice(colorString)
            }

        })
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

    private fun sendDataToDevice(ledNr: Int, r: Int, g: Int, b: Int) {
        val command = "0, $ledNr, $r, $g, $b;\n"

        val count = mDevice.run {
            command.toByteArray().let { buffer ->
                this!!.write(buffer, buffer.size)
            }
        }
        Log.d("WROTE", "Wrote $count bytes to peripheral")
    }

    private fun sendDataToDevice(colors: String) {
        val count = mDevice.run {
            colors.toByteArray().let { buffer ->
                this!!.write(buffer, buffer.size)
            }
        }
        Log.d("WROTE", "Wrote $count bytes to peripheral")
    }

    @Throws(IOException::class)
    fun configureUartFrame(uart: UartDevice) {
        uart.apply {
            // Configure the UART port
            setBaudrate(115200)
            setDataSize(8)
            setParity(UartDevice.PARITY_NONE)
            setStopBits(1)
        }
    }
}
