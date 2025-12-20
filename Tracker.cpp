#include <bits/stdc++.h>
using namespace std;

/* =========================
   CONSTANT DEFINITIONS
   ========================= */
class AppConstants
{
public:
    // Task Names
    static inline const string TASK_REVISE_DOCUMENT = "REVISE DOCUMENT";
    static inline const string TASK_COMPANY_WORK = "COMPANY WORK";
    static inline const string TASK_GFG_DAILY = "GFG DAILY CHALLENGE";
    static inline const string TASK_LEETCODE_DAILY = "LEETCODE DAILY CHALLENGE";
    static inline const string TASK_FINAL_450 = "REVISE FINAL-450 SECTION";
    static inline const string TASK_CODEFORCES = "CF PROBLEM SOLVING";
    static inline const string TASK_LEARN_ENGLISH = "LEARN ENGLISH";
    static inline const string TASK_PUSHUPS = "PUSHUPS";
    static inline const string TASK_WALKING = "WALKING";
    static inline const string TASK_HANDWRITING = "HANDWRITING";
    static inline const string TASK_UPDATE_SHEET = "UPDATE SHEET";
    static inline const string TASK_LAPTOP = "LAPTOP";
    static inline const string TASK_MOBILE = "MOBILE";
    static inline const string TASK_DRIVE = "DRIVE";
    static inline const string TASK_JEE = "JEE";
    static inline const string TASK_EMAIL_IDS = "EMAIL IDs";

    // Sheet Names
    static inline const string SHEET_DAILY_START = "DailyStartSubsheet";
    static inline const string SHEET_COMPANY_WORK = "COMPANYWORK";
    static inline const string SHEET_ONE_TIME = "ONE_TIME TASKS";
    static inline const string SHEET_CODING = "CODING + DEV";
    static inline const string SHEET_PERSONALITY = "PERSONALITY DEVELOPMENT";
    static inline const string SHEET_ORGANISATION = "ORGANISATION";
};

/* =========================
   INPUT UTILITIES
   ========================= */
class InputReader
{
public:
    static int readInt(const string &prompt, int minValue = INT_MIN, int maxValue = INT_MAX)
    {
        while (true)
        {
            cout << prompt;
            int value;
            if (cin >> value)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return max(minValue, min(value, maxValue));
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter an integer.\n";
        }
    }

    static double readDouble(const string &prompt, double minValue, double maxValue)
    {
        while (true)
        {
            cout << prompt;
            double value;
            if (cin >> value)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return max(minValue, min(value, maxValue));
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
        }
    }
};

/* =========================
   DATE / TIME UTILITIES
   ========================= */
class DateUtils
{
public:
    static bool isWeekend()
    {
        time_t now = time(nullptr);
        tm *localTime = localtime(&now);
        return localTime->tm_wday == 0 || localTime->tm_wday == 6;
    }
};

/* =========================
   TASK MODEL
   ========================= */
class Task
{
private:
    string taskName;
    string taskDescription;
    int maxMinutes;
    double maxScore;
    double todayScore;
    bool isDirectScore;

public:
    Task(string name, int maxTime, double maxPoints, string desc = "", bool direct = false)
        : taskName(name), taskDescription(desc), maxMinutes(maxTime),
          maxScore(maxPoints), todayScore(0.0), isDirectScore(direct) {}

    void captureTodayProgress()
    {
        if (isDirectScore)
        {
            double points = InputReader::readDouble(
                "  Points for \"" + taskName + "\" (0 - " + to_string(maxScore) + "): ",
                0.0, maxScore);
            todayScore = points;
            return;
        }

        int minutesSpent = InputReader::readInt(
            "  Time spent on \"" + taskName + "\" (minutes, max " + to_string(maxMinutes) + "): ",
            0, maxMinutes);

        todayScore = (maxMinutes == 0) ? 0.0
                                       : (static_cast<double>(minutesSpent) / maxMinutes) * maxScore;
    }

    double getScore() const { return todayScore; }
    double getMaxScore() const { return maxScore; }
    string getName() const { return taskName; }
};

/* =========================
   TASK GROUP (FORMER SUBSHEET)
   ========================= */
class TaskGroup
{
public:
    enum class TaskType
    {
        DAILY_START,
        COMPANY_WORK,
        ONE_TIME,
        CODING,
        PERSONALITY,
        ORGANISATION
    };

private:
    string groupName;
    vector<Task> tasks;
    bool skipOnWeekend = false;

public:
    TaskGroup(TaskType type)
    {
        switch (type)
        {
        case TaskType::DAILY_START:
            groupName = AppConstants::SHEET_DAILY_START;
            break;
        case TaskType::COMPANY_WORK:
            groupName = AppConstants::SHEET_COMPANY_WORK;
            break;
        case TaskType::ONE_TIME:
            groupName = AppConstants::SHEET_ONE_TIME;
            break;
        case TaskType::CODING:
            groupName = AppConstants::SHEET_CODING;
            break;
        case TaskType::PERSONALITY:
            groupName = AppConstants::SHEET_PERSONALITY;
            break;
        case TaskType::ORGANISATION:
            groupName = AppConstants::SHEET_ORGANISATION;
            break;
        }
    }

    void addTask(const Task &task) { tasks.push_back(task); }
    void setSkipOnWeekend(bool skip) { skipOnWeekend = skip; }

    bool isActiveToday() const
    {
        return !(skipOnWeekend && DateUtils::isWeekend());
    }

    void collectInput()
    {
        cout << "\n--- " << groupName << " ---\n";
        for (auto &task : tasks)
        {
            task.captureTodayProgress();
        }
    }

    double totalScore() const
    {
        double sum = 0;
        for (const auto &task : tasks)
            sum += task.getScore();
        return sum;
    }

    double maxScore() const
    {
        double sum = 0;
        for (const auto &task : tasks)
            sum += task.getMaxScore();
        return sum;
    }

    void printReport() const
    {
        cout << "\n"
             << groupName << ":\n";
        for (const auto &task : tasks)
        {
            cout << "  " << task.getName() << " -> "
                 << task.getScore() << "/" << task.getMaxScore() << "\n";
        }
        cout << "  TOTAL: " << totalScore() << "/" << maxScore() << "\n";
    }

    string getName() const { return groupName; }
};

/* =========================
   TASK GROUP FACTORY
   ========================= */
class TaskGroupFactory
{
public:
    static TaskGroup createDailyStart()
    {
        TaskGroup group(TaskGroup::TaskType::DAILY_START);
        group.addTask(Task(AppConstants::TASK_REVISE_DOCUMENT, 1, 5, "", true));
        return group;
    }

    static TaskGroup createCompanyWork()
    {
        TaskGroup group(TaskGroup::TaskType::COMPANY_WORK);
        group.addTask(Task(AppConstants::TASK_COMPANY_WORK, 1, 50, "", true));
        group.setSkipOnWeekend(true);
        return group;
    }

    static TaskGroup createCoding()
    {
        TaskGroup group(TaskGroup::TaskType::CODING);
        group.addTask(Task(AppConstants::TASK_GFG_DAILY, 10, 5));
        group.addTask(Task(AppConstants::TASK_LEETCODE_DAILY, 10, 5));
        group.addTask(Task(AppConstants::TASK_FINAL_450, 30, 20));
        group.addTask(Task(AppConstants::TASK_CODEFORCES, 30, 20));
        return group;
    }

    static TaskGroup createPersonality()
    {
        TaskGroup group(TaskGroup::TaskType::PERSONALITY);
        group.addTask(Task(AppConstants::TASK_LEARN_ENGLISH, 10, 5));
        group.addTask(Task(AppConstants::TASK_PUSHUPS, 10, 15));
        group.addTask(Task(AppConstants::TASK_WALKING, 40, 15));
        group.addTask(Task(AppConstants::TASK_HANDWRITING, 5, 5));
        return group;
    }

    static TaskGroup createOrganisation()
    {
        TaskGroup group(TaskGroup::TaskType::ORGANISATION);
        group.addTask(Task(AppConstants::TASK_UPDATE_SHEET, 5, 5));
        group.addTask(Task(AppConstants::TASK_LAPTOP, 10, 5));
        group.addTask(Task(AppConstants::TASK_MOBILE, 10, 5));
        group.addTask(Task(AppConstants::TASK_DRIVE, 10, 5));
        group.addTask(Task(AppConstants::TASK_JEE, 30, 5));
        group.addTask(Task(AppConstants::TASK_EMAIL_IDS, 30, 5));
        return group;
    }
};

/* =========================
   MAIN TRACKER
   ========================= */
class ProductivityTracker
{
private:
    map<TaskGroup::TaskType, TaskGroup> taskGroups;

public:
    ProductivityTracker()
    {
        taskGroups.emplace(TaskGroup::TaskType::DAILY_START, TaskGroupFactory::createDailyStart());
        taskGroups.emplace(TaskGroup::TaskType::COMPANY_WORK, TaskGroupFactory::createCompanyWork());
        taskGroups.emplace(TaskGroup::TaskType::CODING, TaskGroupFactory::createCoding());
        taskGroups.emplace(TaskGroup::TaskType::PERSONALITY, TaskGroupFactory::createPersonality());
        taskGroups.emplace(TaskGroup::TaskType::ORGANISATION, TaskGroupFactory::createOrganisation());
    }

    void collectTodayData()
    {
        for (auto &[type, group] : taskGroups)
        {
            if (!group.isActiveToday())
            {
                cout << "Skipping " << group.getName() << " today.\n";
                continue;
            }
            group.collectInput();
        }
    }

    void printSummary() const
    {
        double total = 0, maxTotal = 0;
        cout << "\n========== DAILY SUMMARY ==========" << endl;
        for (const auto &[type, group] : taskGroups)
        {
            if (!group.isActiveToday())
                continue;
            total += group.totalScore();
            maxTotal += group.maxScore();
            cout << group.getName() << ": "
                 << group.totalScore() << "/" << group.maxScore() << endl;
        }
        cout << "\nTOTAL SCORE: " << total << "/" << maxTotal << endl;
        cout << "PRODUCTIVITY: " << (maxTotal ? (total / maxTotal) * 100 : 0) << "%" << endl;
    }

    void printDetailedReport() const
    {
        for (const auto &[type, group] : taskGroups)
        {
            if (group.isActiveToday())
                group.printReport();
        }
    }
};

int main()
{
    ProductivityTracker tracker;
    tracker.collectTodayData();
    tracker.printDetailedReport();
    tracker.printSummary();
    return 0;
}

// Build:
// g++  Tracker.cpp -o tracker
// Run:
// ./tracker
