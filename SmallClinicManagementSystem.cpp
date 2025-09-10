#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class Appointment
class Appointment{
    private:
        string date; // Appointment date
        string time; // Appointment time
        string reason; // Reason for visit
        string status; // Status (Scheduled, Completed, Canceled)

    protected:
    
    public:
        // Constructor for appointment object
        Appointment(string _date, string _time, string _reason, string _status): 
        date(_date), time(_time), reason(_reason), status(_status){}
        
        // Getter functions
        string getDate(){return date;} // Get appointment date
        string getTime(){return time;} // Get appointment time
        string getReason(){return reason;} // Get reason for visit
        string getStatus(){return status;} // Get appointment status

        // Setter functions
        void setDate(string _date){date = _date;} // Change appointment date
        void setTime(string _time){time = _time;} // Change appointment time
        void setReason(string _reason){reason = _reason;} // Change reason for visit
        void setStatus(string _status){status = _status;} // Change appointment status

        // Display appointment information
        void displayAppointment(){
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "Reason: " << reason << endl;
            cout << "Status: " << status << endl;
        }
};

// Class Patients
class Patients{
    private:
    
    protected:
        string name; // Patient name
        string ID; // Patient ID
        int age; // Patient age
        vector<Appointment> medicalHistory; // Medical history (list of appointments)

    public:
        // Constructor for patient object
        Patients(string _name, string _ID, int _age, vector<Appointment> _medicalHistory): 
        name(_name), ID(_ID), age(_age), medicalHistory(_medicalHistory){}

        // Getter functions
        string getName(){return name;} // Get patient name
        string getID(){return ID;} // Get patient ID
        int getAge(){return age;} // Get patient age
        vector<Appointment> getMedicalHistory(){return medicalHistory;} // Get medical history

        // Setter functions
        void setName(string _name){name = _name;} // Change patient name
        void setID(string _ID){ID = _ID;} // Change patient ID
        void setAge(int _age){age = _age;} // Change patient age
        void setMedicalHistory(vector<Appointment> _medicalHistory){medicalHistory = _medicalHistory;} // Change medical history

        // Display patient information
        virtual void displayPatientInfo(){
            cout << "Name: " << name << endl;
            cout << "ID: " << ID << endl;
            cout << "Age: " << age << endl;
        }

        // Schedule a new appointment
        virtual void scheduleAppointment(){
            cout << "Input informations below:\n";

            cout << "Date: ";
            string date;
            cin >> date;
            
            cout << "Time: ";
            string time;
            cin >> time;
            
            cout << "Reason: ";
            string reason;
            cin.ignore();
            getline(cin, reason);
            
            Appointment newAppointment(date, time, reason, "Scheduled");
            medicalHistory.push_back(newAppointment);
        }

        // View medical history
        void viewMedicalHistory(){
            cout << "Medical history:\n";
            for (int i = 0; i < medicalHistory.size(); i++){
                cout << "Appointment " << i + 1 << ":\n";
                medicalHistory[i].displayAppointment();
                cout << endl;
            }
        }

        // Delete an appointment from medical history
        void updateMedicalHistory(){
            cout << "Choose appointment to delete: ";
            int n; cin >> n;
            
            if ((n - 1) >= 0 && (n - 1) < medicalHistory.size()){
                medicalHistory.erase(medicalHistory.begin() + (n - 1));
                cout << "Delete sucessful\n";
            } else cout << "Invalid\n";
        }   
};

// Class ChronicPatients
class ChronicPatients: public Patients{
    private:
        string conditionType; // Type of chronic disease
        string lastCheckUpDate; // Last check-up date
        string frequency; // Check-up frequency
        
    protected:
    
    public:
        // Constructor for chronic patient object
        ChronicPatients(string _name, string _ID, int _age, vector<Appointment> _medicalHistory, string _conditionType, string _lastCheckUpDate, string _frequency)
        : Patients(_name, _ID, _age, _medicalHistory), conditionType(_conditionType), lastCheckUpDate(_lastCheckUpDate), frequency(_frequency) {}

        // Getter functions
        string getConditionType(){return conditionType;}   // Get condition type
        string getLastCheckUpDate(){return lastCheckUpDate;} // Get last check-up date
        string getFrequency(){return frequency;} // Get check-up frequency

        // Setter functions
        void setConditionType(string _conditionType){conditionType = _conditionType;} // Change condition type
        void setLastCheckUpDate(string _lastCheckUpDate){lastCheckUpDate = _lastCheckUpDate;} // Change last check-up date
        void setFrequency(string _frequency){frequency = _frequency;} // Change check-up frequency
        
        // Display chronic patient information
        void displayPatientInfo() override {
            Patients::displayPatientInfo(); 
            cout << "Condition Type: " << conditionType << endl;
            cout << "Last Check-up Date: " << lastCheckUpDate << endl;
        }
        
        // Schedule appointment for chronic patient
        void scheduleAppointment() override {
            Patients::scheduleAppointment(); 
            
            cout << "Condition type: ";
            cin >> conditionType;

            cout << "Last check-up: ";
            cin >> lastCheckUpDate;

            cout << "Appointment scheduled successfully!\n";
            cout << "Reminder: Next follow-up should be scheduled within " << frequency << ".\n";
            
            if (!medicalHistory.empty()) {
                lastCheckUpDate = medicalHistory.back().getDate();  
            }
        }

        // Check regular check-up frequency
        void checkFrequency(){
            cout << "Last check-up date: " << lastCheckUpDate << endl;
            cout << "Frequency: " << frequency << "\n";
        }
};

// Class Doctors
class Doctors{
    private:
        string name; // Doctor name
        string ID; // Doctor ID
        string specialty; // Specialty
        vector<Appointment> assignedAppointments; // List of assigned appointments

    protected:
    
    public:
        // Constructor for doctor object
        Doctors(string _name, string _ID, string _specialty, vector<Appointment> _assignedAppointments): 
        name(_name), ID(_ID), specialty(_specialty), assignedAppointments(_assignedAppointments){}
        
        // Getter functions
        string getName(){return name;} // Get doctor name
        string getID(){return ID;} // Get doctor ID
        string getSpecialty(){return specialty;} // Get specialty
        vector<Appointment> getAssignedAppointments(){return assignedAppointments;} // Get assigned appointments

        // Setter functions
        void setName(string _name){name = _name;} // Change doctor name
        void setID(string _ID){ID = _ID;} // Change doctor ID
        void setSpecialty(string _specialty){specialty = _specialty;} // Change specialty
        void setAssignedAppointments(vector<Appointment> _assignedAppointments){assignedAppointments = _assignedAppointments;} // Change assigned appointments

        // Display doctor information
        void displayDoctorInfo(){
            cout << "Doctor Name: " << name << endl;
            cout << "ID: " << ID << endl;
            cout << "Specialty: " << specialty << endl;
        }
        
        // View assigned appointments
        void viewAssignedAppointments(){
            cout << "Assigned Appointments:\n";
            for (int i = 0; i < assignedAppointments.size(); i++){
                cout << "Appointment " << i + 1 << ":\n";
                assignedAppointments[i].displayAppointment();
                cout << endl;
            }
        }
        
        // Update appointment status
        void updateStatus(){
            cout << "Choose appointment: ";
            int n; cin >> n;
            
            if ((n - 1) >= 0 && (n - 1) <= assignedAppointments.size()){
                cout << "Status: ";
                string status;
                cin >> status;
                
                assignedAppointments[n - 1].setStatus(status);
                cout << "Update sucessful\n";
            } else cout << "Invalid\n";
        }
};

// Class Room
class Room {
private:
    string roomNumber; // Room number
    string department; // Department
    bool available; // Status (available or not)

public:
    // Constructor for room object
    Room(string _roomNumber, string _department, bool _available = true):
    roomNumber(_roomNumber), department(_department), available(_available) {}

    // Getter functions
    string getRoomNumber(){return roomNumber;} // Get room number
    string getDepartment(){return department;} // Get department
    bool isAvailable(){return available;} // Get availability status

    // Setter functions
    void setRoomNumber(string _roomNumber){roomNumber = _roomNumber;} // Set room number
    void setDepartment(string _department){department = _department;} // Set department
    void setAvailability(bool status) { available = status; } // Set availability


    // Display room information
    void displayRoomInfo() {
        cout << "Room Number: " << roomNumber << endl;
        cout << "Department: " << department << endl;
        cout << "Available: ";
        if (available) cout << "Yes\n";
        else cout << "No\n"; 
    }
};

int main() {
    // Create a list of clinic rooms
    vector<Room> clinicRooms = {Room("101", "Cardiology", true), Room("102", "Neurology", false), Room("103", "Pediatrics", true), Room("104", "General Medicine", true)};

    // Role menu
    cout << "Choose your role:\n";
    cout << "1. Patient\n";
    cout << "2. Chronic Patient\n";
    cout << "3. Doctor\n";
    cout << "Your selection: ";
    int mode;
    cin >> mode;

    switch (mode) {
        // Patient
        case 1: { 
            // Create patient1 with medical history
            vector<Appointment> history1;
            history1.push_back(Appointment("7/9/2025", "10:00", "Fever", "Completed"));
            history1.push_back(Appointment("8/9/2025", "09:00", "Flu", "Scheduled"));
            history1.push_back(Appointment("14/8/2025", "15:00", "Headache", "Completed"));
            Patients patient1("Nguyen Van An", "P001", 25, history1);

            // Display patient1 info
            patient1.displayPatientInfo();

            // Function menu
            cout << "Choose function: \n";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. View room\n";
            cout << "Your selection: ";
            int n;
            cin >> n;

            switch (n) {
                // Schedule a new appointment
                case 1: { 
                    patient1.scheduleAppointment();
                    cout << "Appointment scheduled successfully!\n";
                    patient1.viewMedicalHistory();
                    break;
                }

                // View medical history
                case 2: { 
                    patient1.viewMedicalHistory();
                    break;
                }

                // Delete appointment from history
                case 3: { 
                    patient1.updateMedicalHistory();
                    patient1.viewMedicalHistory();
                    break;
                }

                // View clinic rooms
                case 4: { 
                    for (int i = 0; i < clinicRooms.size(); i++){
                        clinicRooms[i].displayRoomInfo();
                        cout << endl;
                    }
                    break;
                }

                // Error case
                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            // Create patient2 with medical history
            vector<Appointment> history2;
            history2.push_back(Appointment("6/9/2025", "14:00", "Cough", "Scheduled"));
            history2.push_back(Appointment("10/9/2025", "11:00", "Fever", "Completed"));
            history2.push_back(Appointment("12/9/2025", "16:00", "Back Pain", "Scheduled"));
            Patients patient2("Le Thi Binh", "P002", 30, history2);

            // Display patient2 info
            patient2.displayPatientInfo();
            
            // Function menu
            cout << "Choose function: \n";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. View room\n";
            cout << "Your selection: ";
            int n;
            cin >> n;
            
            switch (n) {
                // Schedule a new appointment
                case 1: { 
                    patient2.scheduleAppointment();
                    cout << "Appointment scheduled successfully!\n";
                    patient2.viewMedicalHistory();
                    break;
                }
                
                // View medical history
                case 2: {
                    patient2.viewMedicalHistory();
                    break;
                }

                // Delete appointment from history
                case 3: {
                    patient2.updateMedicalHistory();
                    patient2.viewMedicalHistory();
                    break;
                }

                // View clinic rooms
                case 4: {
                    for (int i = 0; i < clinicRooms.size(); i++){
                        clinicRooms[i].displayRoomInfo();
                        cout << endl;
                    }
                    break;
                }

                // Error case
                default: {
                    cout << "Invalid\n";
                    break;
                }
            }
            break;
        }

        // Chronic patient
        case 2: { 
            // Create chronicPatient1 with medical history
            vector<Appointment> history1;
            history1.push_back(Appointment("20/8/2025", "09:00", "Diabetes Checkup", "Completed"));
            history1.push_back(Appointment("22/8/2025", "10:30", "Blood Test", "Completed"));
            history1.push_back(Appointment("25/8/2025", "08:30", "Eye Check", "Scheduled"));
            ChronicPatients chronicPatient1("Tran Van Cuong", "C001", 50, history1, "Diabetes", "20/8/2025", "Every 3 months");
            
            // Display chronicPatient1 info
            chronicPatient1.displayPatientInfo();
            
            // Function menu
            cout << "Choose function: \n";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. Check regular health check-up frequency\n";
            cout << "5. View room\n";
            cout << "Your selection: ";
            int n;
            cin >> n;

            switch (n) {
                // Schedule a new appointment
                case 1: {
                    chronicPatient1.scheduleAppointment();
                    chronicPatient1.viewMedicalHistory();
                    break;
                }
                
                // View medical history
                case 2: {
                    chronicPatient1.viewMedicalHistory();
                    break;
                }

                // Delete appointment from history
                case 3: {
                    chronicPatient1.updateMedicalHistory();
                    chronicPatient1.viewMedicalHistory();
                    break;
                }

                // Check regular health check-up frequency
                case 4: {
                    chronicPatient1.checkFrequency();
                    break;
                }

                // View clinic rooms
                case 5: {
                    for (int i = 0; i < clinicRooms.size(); i++){
                        clinicRooms[i].displayRoomInfo();
                        cout << endl;
                    }
                    break;
                }

                // Error case
                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            // Create chronicPatient2 with medical history
            vector<Appointment> history2;
            history2.push_back(Appointment("10/7/2025", "15:00", "Hypertension Checkup", "Completed"));
            history2.push_back(Appointment("12/7/2025", "09:00", "ECG Test", "Completed"));
            history2.push_back(Appointment("18/7/2025", "13:30", "Kidney Function Test", "Scheduled"));
            ChronicPatients chronicPatient2("Pham Thi Duong", "C002", 60, history2, "Hypertension", "10/7/2025", "Every 6 months");

            // Display chronicPatient2 info
            chronicPatient2.displayPatientInfo();
            
            // Function menu
            cout << "Choose function: \n";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. Check regular health check-up frequency\n";
            cout << "5. View room\n";
            cout << "Your selection: ";
            cin >> n;

            switch (n) {
                // Schedule a new appointment
                case 1: {
                    chronicPatient2.scheduleAppointment();
                    chronicPatient2.viewMedicalHistory();
                    break;
                }
                
                // View medical history
                case 2: {
                    chronicPatient2.viewMedicalHistory();
                    break;
                }

                // Delete appointment from history
                case 3: {
                    chronicPatient2.updateMedicalHistory();
                    chronicPatient2.viewMedicalHistory();
                    break;
                }

                // Check regular health check-up frequency
                case 4: {
                    chronicPatient2.checkFrequency();
                    break;
                }

                // View clinic rooms
                case 5: {
                    for (int i = 0; i < clinicRooms.size(); i++){
                        clinicRooms[i].displayRoomInfo();
                        cout << endl;
                    }
                    break;
                }

                // Error case
                default: {
                    cout << "Invalid\n";
                    break;
                }
            }
            break;
        }

        // Doctor
        case 3: { 
            // Create doctor1 with assigned appointments
            vector<Appointment> doctorApp1;
            doctorApp1.push_back(Appointment("15/8/2025", "10:00", "Fever", "Completed"));
            doctorApp1.push_back(Appointment("16/8/2025", "11:00", "Allergy", "Scheduled"));
            doctorApp1.push_back(Appointment("17/8/2025", "09:30", "Stomach Ache", "Completed"));
            Doctors doctor1("Tran Van Anh", "D001", "Cardiology", doctorApp1);

            // Display doctor1 info
            doctor1.displayDoctorInfo();
            
            // Function menu
            cout << "Choose function:\n";
            cout << "1. View your appointment\n";
            cout << "2. Update appointment status\n";
            cout << "3. Update room status\n";
            cout << "Your selection: ";
            int n;
            cin >> n;

            switch (n) {
                // View assigned appointments
                case 1: { 
                    doctor1.viewAssignedAppointments();
                    break;
                }
                
                // Update appointment status
                case 2: { 
                    doctor1.updateStatus(); 
                    break;
                }

                // Update clinic room availability
                case 3: { 
                    clinicRooms[0].displayRoomInfo();
                    cout << "Status: ";
                    string status;
                    if (status == "Yes" || status == "No"){
                        if (status == "Yes") clinicRooms[0].setAvailability(true);
                        else clinicRooms[0].setAvailability(false);
                        cout << "Update room status sucessful!\n";
                    } else cout << "Invalid\n";
                    break;
                }

                // Error case
                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            // Create doctor2 with assigned appointments
            vector<Appointment> doctorApp2;
            doctorApp2.push_back(Appointment("19/8/2025", "14:00", "Cough", "Scheduled"));
            doctorApp2.push_back(Appointment("20/8/2025", "15:00", "Fever", "Completed"));
            doctorApp2.push_back(Appointment("21/8/2025", "10:30", "General Checkup", "Scheduled"));
            Doctors doctor2("Le Thi Hoa", "D002", "Pediatrics", doctorApp2);

            // Display doctor2 info
            doctor2.displayDoctorInfo();

            // Function menu
            cout << "Choose function:\n";
            cout << "1. View your appointment\n";
            cout << "2. Update appointment status\n";
            cout << "3. Update room status\n";
            cout << "Your selection: ";
            cin >> n;

            switch (n) {
                // View assigned appointments
                case 1: {
                    doctor2.viewAssignedAppointments();
                    break;
                }
                
                // Update appointment status
                case 2: {
                    doctor2.updateStatus(); 
                    break;
                }

                // Update clinic room availability
                case 3: {
                    clinicRooms[2].displayRoomInfo();
                    cout << "Status: ";
                    string status;
                    if (status == "Yes" || status == "No"){
                        if (status == "Yes") clinicRooms[2].setAvailability(true);
                        else clinicRooms[2].setAvailability(false);
                        cout << "Update room status sucessful!\n";
                    } else cout << "Invalid\n";
                    break;
                }

                // Error case
                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            break;
        }

        // Error case when input invalid number
        default:
            cout << "Invalid\n";
            break;
    }
}
/*
All test case:
Test case 1:
- Input:
+ For patient1:
1 (Role selection)
2 (Function Selection)
+ For patient2:
1 (Role selection)
9/9/2025
14:00
Check-up
- Output:
Choose your role:
1. Patient
2. Chronic Patient
3. Doctor
Your selection: 1
Name: Nguyen Van An
ID: P001
Age: 25
Choose function: 
1. Schedule appointment
2. View medical history
3. Update medical history
4. View room
Your selection: 2
Medical history:
Appointment 1:
Date: 7/9/2025
Time: 10:00
Reason: Fever
Status: Completed

Appointment 2:
Date: 8/9/2025
Time: 09:00
Reason: Flu
Status: Scheduled

Appointment 3:
Date: 14/8/2025
Time: 15:00
Reason: Headache
Status: Completed

Name: Le Thi Binh
ID: P002
Age: 30
Choose function: 
1. Schedule appointment
2. View medical history
3. Update medical history
4. View room
Your selection: 1
Input informations below:
Date: 9/9/2025
Time: 14:00
Reason: Check-up
Appointment scheduled successfully!
Medical history:
Appointment 1:
Date: 6/9/2025
Time: 14:00
Reason: Cough
Status: Scheduled

Appointment 2:
Date: 10/9/2025
Time: 11:00
Reason: Fever
Status: Completed

Appointment 3:
Date: 12/9/2025
Time: 16:00
Reason: Back Pain
Status: Scheduled

Appointment 4:
Date: 9/9/2025
Time: 14:00
Reason: Check-up
Status: Scheduled
*/
