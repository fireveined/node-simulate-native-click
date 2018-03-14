var addon = require('./build/Release/addon');

enum Type {
        LEFT,
        RIGHT
}

class SimulateNativeClick {

        private click(type: Type, hwnd: number | Buffer, x: number, y: number) {
                if (type === undefined || x === undefined || y === undefined)
                        throw new Error("Invalid parameters - can't be undefined");

                let hwndNumber;

                if (hwnd instanceof Buffer) {
                        hwndNumber = hwnd.readUInt32LE(0);
                }
                else {
                        hwndNumber = hwnd;
                }


                if (type == Type.LEFT)
                        addon.leftClick(hwndNumber, x, y)
                else if (type == Type.RIGHT)
                        addon.rightClick(hwndNumber, x, y)
        }

        public right(hwnd: number | Buffer, x: number, y: number): void {
                this.click(Type.RIGHT, hwnd, x, y);
        }

        public left(hwnd: number | Buffer, x: number, y: number): void{
                this.click(Type.LEFT, hwnd, x, y);
        }

}
var simulateNativeClick = new SimulateNativeClick();
module.exports = simulateNativeClick;