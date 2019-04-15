package io.vanpana.multiled

import java.net.Socket
import java.util.*

class ClientHandler(client: Socket, val ledColorChanged: LedColorChanged) {
    private val client: Socket = client
    private val reader: Scanner = Scanner(client.getInputStream())
    private var running: Boolean = false

    fun run() {
        running = true

        while (running) {
            try {
                val text = reader.nextLine()
                text.trim('\n')

                ledColorChanged.colorChanged(text)
            } catch (ex: Exception) {
                // TODO: Implement exception handling
                shutdown()
            } finally {

            }

        }
    }

    private fun shutdown() {
        running = false
        client.close()
        println("${client.inetAddress.hostAddress} closed the connection")
    }
}