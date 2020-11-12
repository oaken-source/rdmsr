# OSM RDMSR playground

--

Ein einfacher Programmrahmen. Ihnen zur Hilfe um Ihren Tutoren die Unterschiede zwischen Kernel- und Usermode zu demonstrieren (auf Linux 3+).

In `rdmsr.h` ist ein direkter Aufruf der privilegierten x86_64-Instruktion [**R**ea**d** **M**odel **S**pecific **R**egister](https://www.felixcloutier.com/x86/RDMSR.html) mithilfe von Inline-Assembler vordefiniert. Dort finden Sie auch einige Beispiele für interessante Registernummern, die Sie mithilfe von `__assembly_rdmsr` auslesen können und Wege um die Ergebnisse zu prüfen.

Es müssen die Kernel-Header, ein C-Compiler und `make` installiert sein. Auf Debian-basierenden Linux-Distributionen hierzu folgendes ausführen:

	sudo apt-get install build-essential linux-headers-`uname -r`

Beim Aufruf von `make` werden folgende Dateien erzeugt:

* `user_rdmsr`: Ein im Userspace ausführbares Programm.
* `kernel_rdmsr.ko`: Ein nachladbares Kernelmodul (vergleichbar mit einem Gerätetreiber).

### Sicherheitshinweise

Damit das Kernelmodul gebaut werden kann, darf der Pfad zu Ihrem Quelltext keine Leer- oder Sonderzeichen enthalten.

Führen Sie Ihren Kernelcode nicht auf Ihrem Produktivsystem aus. Nutzen Sie lieber eine VM!

Moderne Linux-Systeme versuchen einfache Fehler (*Oops*) abzufangen. Sie können dies (temporär) deaktivieren:

	sudo sh -c 'echo 1 > /proc/sys/kernel/panic_on_oops'

### Cheat-Sheet

| Kommando                          | Bedeutung                                         |
|-----------------------------------|---------------------------------------------------|
| `sudo insmod kernel_rdmsr.ko`     | Kernelmodul laden                                 |
| `sudo rmmod kernel_rdmsr`         | Kernelmodul entfernen (ohne `.ko`!)               |
| `lsmod`                           | Geladene Kernelmodule auflisten                   |
| `dmesg`                           | Kernelausgaben anzeigen (z.B. `printk`)           |
| `sudo dmesg -c`                   | Neue Ausgaben seit dem letzten `-c` Aufruf zeigen |
| `make CFLAGS=-g clean user_rdmsr` | Debugsymbole für `gdb` einfügen (Userspace)       |
