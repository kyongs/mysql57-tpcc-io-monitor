# mysql57-tpcc-io-monitor

## Build and Install
1. Clone the source code:
  ```
  $ git clone https://github.com/kyongs/mysql57-tpcc-io-monitor.git
  ```

2. Modify the `PASSWD`, `BUILD_DIR`, `BASE_DIR` value in tpcc-monitor-build.sh script file: <br/>
   You may also have to modify the number of `make -j` option. This option depends on number of  cpu cores.
  ```
  $ vi tpcc-monitor-build.sh
  
  #!/bin/bash
  
  BASE_DIR=`pwd -P`
  BUILD_DIR=$BASE_DIR/bld
  PASSWD="sudo-passwd"
  ...
  
  make -j16
  ...
  ```


3. Run the script file:

```
$ ./tpcc-monitor-build.sh 
```
|Option | Description|
|---|---|
| --origin | Vanilla version |
| --tpcc | Monitor tpcc tables (`default`) | 

If you want to execute vanilla version, you can run the script as follows:
```
$ ./tpcc-monitor-build.sh --origin
```

## Results
TBA
