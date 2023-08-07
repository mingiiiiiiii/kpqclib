# KPQClib

This project is motivated by [PQClean](https://github.com/PQClean/PQClean).

We provide all of [KPQC](https://www.kpqc.or.kr/competition.html) Competition Algorithms with benchmarking, KAT and Metamorphic testing.

All OpenSSL dependencies are removed, and we used cryptographic algorithms in PQClean.

## How to build
Before you build, check the ```requirements.txt``` file and ensure you installed the required tool.

First, clone the repository. Then, run CMake and Make at the root directory.

Do NOT run ```make``` in each directory. It may occur some errors.
```
cmake .
make
```

If you want to cancel the build, then run clean.
```
make clean
```

### How to build Layered ROLLO-I and FIBS
#### Layered ROLLO-I
Before building, you have to install GMP and NTL libraries. Run the following commands.
```
sudo apt update
sudo apt install libgmp-dev
sudo apt install libntl-dev
```

Move to ```KPQClib\crypto_kem\Layered_ROLLO\Reference_implementation_221201```, then run ```python3 rbc-lib.py```. It will automatically check the configurations and start building.

#### FIBS
Move to ```KPQClib\crypto_sign\FIBS```, then run ```make```.

## FAQ
### Segmentation fault(or stack corruption) during run PALOMA family
To run PALOMA family, you need to increase the stack size to 51200.
```
ulimit -s 51200
```

### Metamorphic test result is not the same as the given table in README.
To run metamorphic testing, you should fix the random values.
Try after fixing the ```randombytes``` functions into fixed values. We left them in the comments for each function.

## Metamorphic Testing
### KEM
|Algorithm|Bit Cont. Test|Bit Excl. Test|Enc. Dec. Test|Done|Note|
|:---:|:---:|:---:|:---:|:---:|:---:|
|IPCC f1||||X|Cannot run in Ubuntu|
|IPCC f3||||X|Cannot run in Ubuntu|
|IPCC f4||||X|Cannot run in Ubuntu|
|Layered ROLLO|S|S|S|O||
|PALOMA 128|S|S|S|O||
|PALOMA 192|S|S|S|O||
|PALOMA 256|S|S|S|O||
|SMAUG 1|S|S|S|O||
|SMAUG 3|S|S|S|O||
|SMAUG 5|S|S|S|O||
|TIGER 128|<span style="color:red"> F </span>|S|S|O|check sk only 0x01, and 0xff -> BCT fail|
|TIGER 192|<span style="color:red"> F </span>|S|S|O|check sk only 0x01, and 0xff -> BCT fail|
|TIGER 256|<span style="color:red"> F </span>|S|S|O|check sk only 0x01, and 0xff -> BCT fail|
|NTRU+ 576|S|S|S|O||
|NTRU+ 768|S|S|S|O||
|NTRU+ 864|S|S|S|O||
|NTRU+ 1152|S|S|S|O||

## DSA
|Algorithm|Bit Cont. Test|Bit Excl. Test|Bit Vrfy. Test|Done|Note|
|:---:|:---:|:---:|:---:|:---:|:---:|
|AIMer L1|S|S|S|O||
|AIMer L3|S|S|S|O||
|AIMer L5|S|S|S|O||
|Enhanced pqsigRM 612|S|S|S|O||
|Enhanced pqsigRM 613|S|S|S|O||
|FIBS|S|S|S|O||
|GCKSign II|S|S|S|O||
|GCKSign III|S|S|S|O||
|GCKSign V|S|S|S|O||
|HAETAE 2|S|S|S|O||
|HAETAE 3|S|S|S|O||
|HAETAE 5|S|S|S|O||
|MQ-Sign 72-46|S|S|S|O||
|MQ-Sign 112-72|S|S|S|O||
|NCC-Sign 2|S|S|S|O||
|NCC-Sign 3|S|S|S|O||
|NCC-Sign 5|S|S|S|O||
|Peregrine 512|S|S|S|O||
|Peregrine 1024|S|S|S|O||
|SOLMAE 512|S|S|S|O||
|SOLMAE 1024|S|S|S|O||


