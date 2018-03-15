# simulate-native-click

> Simple C++/WinApi addon that allow to simulate native clicks. TypeScript definitions inside.

## Install

```bash
npm install simulate-native-click --save
```

## Usage

```javascript
var simulateClick = require("simulate-native-click");

let x = 100;
let y = 200;
simulateClick.left(hwnd, x, y);

x = 300;
y = 300;
simulateClick.right(hwnd, x, y);

simulateClick.getMousePosition(hwnd); // {x, y}
// position relative to window

simulateClick.getMousePosition(); // {x, y}
// global screen position returned if no hwnd provided
```

You can obtain HWND using `winctl` package
https://www.npmjs.com/package/winctl

```javascript
var win = winctl.GetActiveWindow();

let hwnd =  win.getHwnd();
let x = 100;
let y = 200;
simulateClick.left(hwnd, x, y);
```

You can also use it with electron:

```javascript
let hwnd =  mainWindow.getNativeWindowHandle();
let x = 100;
let y = 200;
simulateClick.left(hwnd, x, y);
```
