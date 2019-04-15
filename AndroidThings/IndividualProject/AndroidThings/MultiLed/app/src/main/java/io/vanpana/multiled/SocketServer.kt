package io.vanpana.multiled

import java.net.ServerSocket
import kotlin.concurrent.thread

class SocketServer() {
    val server = ServerSocket(6969)

    fun run(ledColorChanged: LedColorChanged) {
        thread {
            while (true) {
                val client = server.accept()
                println("Client connected: ${client.inetAddress.hostAddress}")

                // Run client in it's own thread.
                thread { ClientHandler(client, ledColorChanged).run() }
            }
        }
    }
}