# Log Analyser

## How to use

### Compilation:
```
make
```

### Run:
 ```
 ./bin/analog -e -g graph.dot -t 13 ./Tests/logs/anonyme.log
 ```
 
Note: make sure that the log file is always at the end.

## Testing

To test it, make sure to change directory to `Cpp-TP4/tests` and run the `mktest.sh` script.

## Other

We implemented that the `-g` flag only takes `*.dot` file names because it prevents accidentally rewriting the the log file.