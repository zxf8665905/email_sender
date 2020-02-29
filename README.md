# Email Sender
A email send tool.

## Steup
```bash
git clone https://github.com/zxf8665905/email_sender.git
cd email_sender && mkdir build && cd build
cmake .. && make
```

## Sender email (use default config)
```bash
cp ../example/config.example config.txt
./email
```

## Sender email (use custom config)
```bash
cp ../example/config.example config.txt
vi "config.txt" # to custom your sender email config.
./email
```
