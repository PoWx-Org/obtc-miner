oBTC Miner
==========

obtc-miner is a fork supporting oBTC (Optical Bitcoin) network.
oBTC is an experimental currency based on Bitcoin. See more on
https://powx.org.

obtc-miner is based on cpuminer-opt, a fork of cpuminer-multi by TPruvot with optimizations
imported from other miners developped by lucas Jones, djm34, Wolf0, pooler,
Jeff garzik, ig0tik3d, elmad, palmd, and Optiminer, with additional
optimizations by Jay D Dee.

All of the code is believed to be open and free. If anyone has a
claim to any of it post your case in the cpuminer-opt Bitcoin Talk forum
or by email.

Miner programs are often flagged as malware by antivirus programs. This is
a false positive, they are flagged simply because they are cryptocurrency 
miners. The source code is open for anyone to inspect. If you don't trust 
the software, don't use it.


Bitcointalk threads:

* https://bitcointalk.org/index.php?topic=5226770.msg53865575#msg53865575
* https://bitcointalk.org/index.php?topic=1326803.0


See file RELEASE_NOTES for change log and INSTALL_LINUX or INSTALL_WINDOWS
for compile instructions.

Requirements
------------

1. A x86_64 architecture CPU with a minimum of SSE2 support. This includes
Intel Core2 and newer and AMD equivalents. Further optimizations are available
on some algoritms for CPUs with AES, AVX, AVX2, SHA, AVX512 and VAES.

Older CPUs are supported by cpuminer-multi by TPruvot but at reduced
performance.

ARM and Aarch64 CPUs are not supported.

2. 64 bit Linux or Windows OS. Ubuntu and Fedora based distributions,
including Mint and Centos, are known to work and have all dependencies
in their repositories. Others may work but may require more effort. Older
versions such as Centos 6 don't work due to missing features. 
64 bit Windows OS is supported with mingw_w64 and msys or pre-built binaries.

MacOS, OSx and Android are not supported.

3. Stratum pool supporting stratum+tcp:// or stratum+ssl:// protocols or
RPC getwork using http:// or https://.
GBT is YMMV.


Errata
------

AMD CPUs older than Piledriver, including Athlon x2 and Phenom II x4, are not
supported due to an incompatible implementation of SSE2 on
these CPUs. Some algos may crash the miner with an invalid instruction.


Bugs
----

Users are encouraged to post their bug reports using Github issues:
https://github.com/PoWx-Org/obtc-miner/issues

All problem reports must be accompanied by a proper problem definition.
This should include how the problem occurred, the command line and
output from the miner showing the startup messages and any errors.
A history is also useful, ie did it work before.


Happy mining!

