var addon = require('./build/Release/addon');
var Type;
(function (Type) {
    Type[Type["LEFT"] = 0] = "LEFT";
    Type[Type["RIGHT"] = 1] = "RIGHT";
})(Type || (Type = {}));
var SimulateNativeClick = /** @class */ (function () {
    function SimulateNativeClick() {
    }
    SimulateNativeClick.prototype.click = function (type, hwnd, x, y) {
        if (type === undefined || x === undefined || y === undefined)
            throw new Error("Invalid parameters - can't be undefined");
        var hwndNumber;
        if (hwnd instanceof Buffer) {
            hwndNumber = hwnd.readUInt32LE(0);
        }
        else {
            hwndNumber = hwnd;
        }
        if (type == Type.LEFT)
            addon.leftClick(hwndNumber, x, y);
        else if (type == Type.RIGHT)
            addon.rightClick(hwndNumber, x, y);
    };
    SimulateNativeClick.prototype.right = function (hwnd, x, y) {
        this.click(Type.RIGHT, hwnd, x, y);
    };
    SimulateNativeClick.prototype.left = function (hwnd, x, y) {
        this.click(Type.LEFT, hwnd, x, y);
    };
    return SimulateNativeClick;
}());
var simulateNativeClick = new SimulateNativeClick();
module.exports = simulateNativeClick;
