#/bin/bash

./cipher DES 0123456789abcdef ENC in.txt out.enc
./cipher DES 0123456789abcdef DEC out.enc smalldes.dec

./cipher DES 0123456789abcdef ENC big.txt out.enc
./cipher DES 0123456789abcdef DEC out.enc bigdes.dec

./cipher AES 00123456789abcdef ENC in.txt out.enc
./cipher AES 00123456789abcdef DEC out.enc smallaes.dec

./cipher AES 00123456789abcdef ENC big.txt out.enc
./cipher AES 00123456789abcdef DEC out.enc bigaes.dec


