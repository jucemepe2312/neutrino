# Neutrino 🕵️‍♂️

Sniffer de red (analizador de tráfico) en C puro para Linux. Escucha el tráfico de tu tarjeta de red y muestra las conexiones TCP y UDP que pasan por ella.

Parte del ecosistema de herramientas de sistema con temática de física de partículas: **Quark**, **Neutron**, **Photon**, **Tachyon**, **Gluon**, **Electron**, **Neutrino**, **Átomo**.

## ¿Qué hace?

Neutrino abre un *raw socket* (`AF_PACKET`), captura los paquetes que llegan a tu tarjeta de red, y parsea las cabeceras de Ethernet, IPv4, TCP y UDP. Muestra la IP de origen, IP de destino y los puertos de cada conexión, en tiempo real.

### Ejemplo de salida

```text
[TCP] 192.168.1.10:49318 -> 93.243.107.34:443
[TCP] 93.243.107.34:443 -> 192.168.1.10:49318
[UDP] 192.168.1.10:53 -> 8.8.8.8:53