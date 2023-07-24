# 🌟 LEO-Satellite-Communication-Simulation-Platform
LEO-Satellite-Communication-Simulation-Platform based on STK &amp; OPNET
>>>>>>> 3812f6c13ba6fc5f2bbed5dad36ca750332ead87

## 🛷 How to use

### Build
windows - MinGW - make
```terminal
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

windows - ninja
```terminal
mkdir build
cd build
cmake -G "Ninja" ..
cmake --build .
```

### Run

```terminal
./bin/LEO
```

## 🎄 Project Structure

```terminal
├─bin                   // Executable files
├─dependencies          // Third-party librariesr
│  ├─include
│  └─stk
│      ├─Debug
│      └─Release
├─include               // Header files
├─libs                  // Static libraries
│  ├─Debug
│  └─Release
├─src                   // Source files
└─test                  // Test files
```