# php-md5-brute

Bruteforcing MD5 hashes of the form 0e[0-9]{30} with a chosen message prefix.

```
  > make
  > ./brute foo
  Input: foo
  [10 MHashes | 5.85 MHashes/s] [ 4079a53ecdf75d0e5f5746a0a811a096 ]
  ...
  Found hash after 72753295 iterations! 
  Input: "foo58124616"
  Hash: 0e920554035759404500650980227149
```
