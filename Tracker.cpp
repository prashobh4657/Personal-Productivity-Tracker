#include <bits/stdc++.h>
using namespace std;

class Constants {
public:
    static inline const string REVISE_DOCUMENT = "REVISE DOCUMENT";
    static inline const string COMPANY_WORK = "COMPANY WORK";
    static inline const string GFG_DAILY_CHALLENGE = "GFG DAILY CHALLENGE";
    static inline const string LEETCODE_DAILY_CHALLENGE = "LEETCODE DAILY CHALLENGE";
    static inline const string REVISE_FINAL_450_SECTION = "REVISE FINAL-450 SECTION";
    static inline const string CF_PROBLEM_SOLVING = "CF PROBLEM SOLVING";
    static inline const string LEARN_ENGLISH = "LEARN ENGLISH";
    static inline const string PUSHUPS = "PUSHUPS";
    static inline const string WALKING = "WALKING";
    static inline const string HANDWRITING = "HANDWRITING";
    static inline const string UPDATE_SHEET = "UPDATE SHEET";
    static inline const string LAPTOP = "LAPTOP";
    static inline const string MOBILE = "MOBILE";
    static inline const string DRIVE = "DRIVE";
    static inline const string JEE = "JEE";
    static inline const string EMAIL_IDS = "EMAIL IDs";
    static inline const string SHEET_DAILY_START = string("DailyStartSubsheet");
    static inline const string SHEET_COMPANY_WORK = string("COMPANYWORK");
    static inline const string SHEET_ONE_TIME = string("ONE_TIME TASKS");
    static inline const string SHEET_CODING = string("CODING + DEV");
    static inline const string SHEET_PERSONALITY = string("PERSONALITY DEVELOPMENT");
    static inline const string SHEET_ORGANISATION = string("ORGANISATION");
};

class InputUtility {
public:
    static int readInt(const string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
        while (true) {
            cout << prompt;
            int v;
            if (cin >> v) {
                string rest; getline(cin, rest);
                if (v < minVal) v = minVal;
                if (v > maxVal) v = maxVal;
                return v;
            }
            cin.clear(); string junk; getline(cin, junk);
            cout << "Invalid input, please enter an integer.\n";
        }
    }

    static double readDouble(const string& prompt, double minVal = -numeric_limits<double>::infinity(), double maxVal = numeric_limits<double>::infinity()) {
        while (true) {
            cout << prompt;
            double v;
            if (cin >> v) {
                string rest; getline(cin, rest);
                if (v < minVal) v = minVal;
                if (v > maxVal) v = maxVal;
                return v;
            }
            cin.clear(); string junk; getline(cin, junk);
            cout << "Invalid input, please enter a number.\n";
        }
    }
};

class TrackerUtility {
public:
    static bool todayIsWeekend() {
        std::time_t t = std::time(nullptr);
        std::tm *lt = std::localtime(&t);
        int wday = lt->tm_wday;
        return (wday == 0 || wday == 6);
    }
};

class Task {
    string name;
    string description;
    int maxTime;        
    double maxPoints;
    double todayPoints = 0.0;
    bool directInput = false;

public:
    Task(string name, int maxTime, double maxPoints, string description = "", bool directInput = false) {
        this->name = name;
        this->description = description;
        this->maxTime = maxTime;
        this->maxPoints = maxPoints;
        this->todayPoints = 0.0;
        this->directInput = directInput;
    }

    void collectTodayInput() {
        if (directInput) {
            double pts = InputUtility::readDouble("  Points for \"" + name + "\" (0 - " + to_string(maxPoints) + "): ", 0.0, maxPoints);
            setPoints(pts);
            return;
        }

        int timeSpent = InputUtility::readInt("  Time spent on \"" + name + "\" (minutes, max " + to_string(maxTime) + "): ", 0, INT_MAX);
        calculatePoints(timeSpent);
    }

    void calculatePoints(int timeSpent) {
        if (maxTime <= 0) {
            todayPoints = 0.0;
            return;
        }

        if (timeSpent < 0)
            timeSpent = 0;

        if (timeSpent > maxTime) {
            todayPoints = maxPoints;
            return;
        }

        double fraction = (double)timeSpent / maxTime;
        todayPoints = fraction * maxPoints;
    }

    void setPoints(double pts) {
        if (pts < 0.0) pts = 0.0;
        if (pts > maxPoints) pts = maxPoints;
        todayPoints = pts;
    }

    double getTodayPoints() { return todayPoints; }
    double getMaxPoints() { return maxPoints; }
    string getName() { return name; }
    string& getDescription() { return description; }
};

class SubSheet {
public:
    enum SubSheetType { DAILY_START = 0, COMPANY_WORK = 1, ONE_TIME = 2, CODING = 3, PERSONALITY = 4, ORGANISATION = 5 };

public:

    SubSheet(SubSheetType t) {
        this->type = t;
        switch (t) {
            case DAILY_START: name = Constants::SHEET_DAILY_START; break;
            case COMPANY_WORK: name = Constants::SHEET_COMPANY_WORK; break;
            case ONE_TIME: name = Constants::SHEET_ONE_TIME; break;
            case CODING: name = Constants::SHEET_CODING; break;
            case PERSONALITY: name = Constants::SHEET_PERSONALITY; break;
            case ORGANISATION: name = Constants::SHEET_ORGANISATION; break;
            default: name = "UNKNOWN"; break;
        }
    }

    void addTask(Task task) {
        tasks.push_back(task);
    }

    string getName() { return name; }
    SubSheetType getType() { return type; }

    void setSkipOnWeekend(bool v) { skipOnWeekend = v; }
    bool isIncludeSubSheet()  { return !(skipOnWeekend && TrackerUtility::todayIsWeekend()); }

    void inputToday() {
        cout << "\n--- " << name << " ---\n";
        for (auto& t : tasks)
            t.collectTodayInput();
    }

    double getTodayPoints() {
        double sum = 0;
        for (auto& t : tasks)
            sum += t.getTodayPoints();
        return sum;
    }

    double getMaxPoints() {
        double sum = 0;
        for (auto& t : tasks)
            sum += t.getMaxPoints();
        return sum;
    }

    void setTaskPointsByName(const string& taskName, double pts) {
        for (auto& t : tasks) {
            if (t.getName() == taskName) {
                t.setPoints(pts);
                return;
            }
        }
    }

    void printReport() {
        cout << "\n" << name << ":\n";
        for (auto& t : tasks) {
            cout << "  " << t.getName();
            if (!t.getDescription().empty())
                cout << " (" << t.getDescription() << ")";
            cout << " -> " << t.getTodayPoints()
                 << "/" << t.getMaxPoints() << "\n";
        }
        cout << "  TOTAL: "
             << getTodayPoints() << "/"
             << getMaxPoints() << "\n";
    }

private:
    string name;
    vector<Task> tasks;
    SubSheetType type = ONE_TIME;
    bool skipOnWeekend = false;
};

class SubSheetFactory {
public:
    static SubSheet createDailyStart() {
        SubSheet s(SubSheet::DAILY_START);
        s.addTask(Task(Constants::REVISE_DOCUMENT, 1, 5, "", true));
        return s;
    }

    static SubSheet createCompanyWork() {
        SubSheet s(SubSheet::COMPANY_WORK);
        s.addTask(Task(Constants::COMPANY_WORK, 1, 50, "", true));
        s.setSkipOnWeekend(true);
        return s;
    }

    static SubSheet createCoding() {
        SubSheet s(SubSheet::CODING);
        s.addTask(Task(Constants::GFG_DAILY_CHALLENGE, 10, 5, "", false));
        s.addTask(Task(Constants::LEETCODE_DAILY_CHALLENGE, 10, 5, "", false));
        s.addTask(Task(Constants::REVISE_FINAL_450_SECTION, 30, 20, "", false));
        s.addTask(Task(Constants::CF_PROBLEM_SOLVING, 30, 20, "", false));
        return s;
    }

    static SubSheet createPersonality() {
        SubSheet s(SubSheet::PERSONALITY);
        s.addTask(Task(Constants::LEARN_ENGLISH, 10, 5, "", false));
        s.addTask(Task(Constants::PUSHUPS, 10, 15, "", false));
        s.addTask(Task(Constants::WALKING, 40, 15, "", false));
        s.addTask(Task(Constants::HANDWRITING, 5, 5, "", false));
        return s;
    }

    static SubSheet createOrganisation() {
        SubSheet s(SubSheet::ORGANISATION);
        s.addTask(Task(Constants::UPDATE_SHEET, 5, 5, "", false));
        s.addTask(Task(Constants::LAPTOP, 10, 5, "", false));
        s.addTask(Task(Constants::MOBILE, 10, 5, "", false));
        s.addTask(Task(Constants::DRIVE, 10, 5, "", false));
        s.addTask(Task(Constants::JEE, 30, 5, "", false));
        s.addTask(Task(Constants::EMAIL_IDS, 30, 5, "", false));
        return s;
    }

    static SubSheet createOneTime() {
        SubSheet s(SubSheet::ONE_TIME);
        return s;
    }
};

class Tracker {
    std::map<SubSheet::SubSheetType, SubSheet> sheets;

public:
    Tracker() {
        sheets.emplace(SubSheet::DAILY_START, SubSheet(SubSheet::DAILY_START));
        sheets.emplace(SubSheet::COMPANY_WORK, SubSheet(SubSheet::COMPANY_WORK));
        sheets.emplace(SubSheet::ONE_TIME, SubSheet(SubSheet::ONE_TIME));
        sheets.emplace(SubSheet::CODING, SubSheet(SubSheet::CODING));
        sheets.emplace(SubSheet::PERSONALITY, SubSheet(SubSheet::PERSONALITY));
        sheets.emplace(SubSheet::ORGANISATION, SubSheet(SubSheet::ORGANISATION));
    }

    void configure() {
        sheets.insert_or_assign(SubSheet::DAILY_START, SubSheetFactory::createDailyStart());
        sheets.insert_or_assign(SubSheet::COMPANY_WORK, SubSheetFactory::createCompanyWork());
        sheets.insert_or_assign(SubSheet::CODING, SubSheetFactory::createCoding());
        sheets.insert_or_assign(SubSheet::PERSONALITY, SubSheetFactory::createPersonality());
        sheets.insert_or_assign(SubSheet::ORGANISATION, SubSheetFactory::createOrganisation());
        sheets.insert_or_assign(SubSheet::ONE_TIME, SubSheetFactory::createOneTime());
    }

    void inputToday() {
        for (auto &kv : sheets) {
            auto &s = kv.second;
            if (!s.isIncludeSubSheet()) {
                cout << "Skipping " << s.getName() << " for today.\n";
                continue;
            }
            s.inputToday();
        }
    }

    void printMainReport() {
        double total = 0.0, totalMax = 0.0;
        cout << "\n========== MAIN SHEET ==========\n";
        for (auto &kv : sheets) {
            auto &s = kv.second;
            if (!s.isIncludeSubSheet()) {
                cout << s.getName() << ": skipped for today\n";
                continue;
            }
            double pts = s.getTodayPoints();
            double mx = s.getMaxPoints();
            cout << s.getName() << ": " << pts << "/" << mx << "\n";
            total += pts;
            totalMax += mx;
        }

        cout << "\nTOTAL POINTS: " << total << "/" << totalMax << "\n";
        if (totalMax > 0)
            cout << "PRODUCTIVITY: " << (total / totalMax) * 100 << "%\n";
        else
            cout << "PRODUCTIVITY: N/A\n";
    }

    void printDetailedReport() {
        for (auto &kv : sheets) {
            auto &s = kv.second;
            if (!s.isIncludeSubSheet()) {
                cout << "\n" << s.getName() << ": skipped for today\n";
                continue;
            }
            s.printReport();
        }
    }

};

int main() {
    Tracker tracker;
    tracker.configure();
    tracker.inputToday();
    tracker.printDetailedReport();
    tracker.printMainReport();
    return 0;
}

// Run Tracker.cpp : 
// Command 1 : g++ -std=c++17 -O2 -g Tracker.cpp -o Tracker
// Command 2 : ./Tracker