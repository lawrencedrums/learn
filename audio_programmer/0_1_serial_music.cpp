class Dodecaphonic {
    protected:
    int series[12];

    int mod12(int note) {
        while (note >= 12) note -= 12;
        while (note < 0) note += 12;
        return note;
    }

    public:
    Dodecaphonic() { // Default constructor
        for (int i = 0; i < 12; i++) {
            series[i] = 0;
        }
    }

    
}
