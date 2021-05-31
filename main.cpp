#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

class Clock {
public:
    [[noreturn]] Clock() {

        cout << "[The Imperial Clock]" << "\n 10 h   = 1 d" << "\n 10 min = 1 h" << "\n 10 sec = 1 min"
             << "\n 10 ds  = 1 sec" << endl;

        cout << "[#:#:#:#]";

        while (true) {
            print_time();


            this_thread::sleep_for(chrono::milliseconds(864));
        }
    }

    int get_millisecond_of_day() {
        auto now = chrono::system_clock::now();
        time_t tt = chrono::system_clock::to_time_t(now);
        tm local_time = *localtime(&tt);

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) -
                  std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

        return (((local_time.tm_hour * 60) + local_time.tm_min) * 60 + local_time.tm_sec) * 1000 + ms.count();
    }

    void print_time() {
        int ms = get_millisecond_of_day();

        int hours = ms / 8640000;
        int minutes = (ms - (hours * 8640000)) / 864000;
        int seconds = (ms - (hours * 8640000 + minutes * 864000)) / 86400;
        int ds = (ms - (hours * 8640000 + minutes * 864000 + seconds * 86400)) / 8640;

        cout << string(9, '\b') << "[" << to_string(hours) << ":" << to_string(minutes) << ":" << to_string(seconds)
             << ":" << to_string(ds) << "]";

    }


};

int main() {

    Clock();

}
