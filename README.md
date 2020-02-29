# Email Sender
A email send tool.

## steup
```bash
mkdir build && cd build
cmake ..
make
```

## sender email (use default config)
```bash
cp ../example/config.example config.txt
./email
```

## sender email (use custom config)
```bash
cp ../example/config.example config.txt
vi "config.txt" # to custom your sender email config.
./email
```
