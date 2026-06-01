/*
* Class for simlulating an integer cell.
*/

class IntCell {
public:
    /*IntCell() {
        storedValue = 0;
    }*/

    explicit IntCell(int initialVal = 0) {
        storedValue = initialVal;
    }

    IntCell(int val1, int val2) : storedValue{ val1 + val2 } {}

    int read() const {
        return storedValue;
    }

    void write(int newVal) {
        storedValue = newVal;
    }
private:
    int storedValue;
};