class Line {
private:
    bool changed;
    double length;
    Point start;
    Point end;

public:
    void setStart(Point p) {
        start = p;
        changed = true;
    }
    void setEnd(Point p) {
        end = p;
        changed = true;
    }
    Point getStart(void) { return start; }
    Point getEnd(void) { return end; }
    double length() {
        if (changed) {
            length = start.distanceTo(end);
            changed = false;
        }
        return length;
    }
};
