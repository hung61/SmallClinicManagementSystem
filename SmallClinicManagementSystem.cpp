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
    
    public:
        // Constructor for appointment object
        Appointment(string _date, string _time, string _reason, string _status): 
        date(_date), time(_time), reason(_reason), status(_status){}
        
        // Display appointment information
        void displayAppointment(){
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "Reason: " << reason << endl;
            cout << "Status: " << status << endl;
        }
        
        // Get appointment date
        string getDate(){
            return date;
        }
        
        // Update appointment status
        void setStatus(string _status){
            status = _status;
        }
};

// Class Patient
class Patients{
    protected:
        string name; // Patient name
        string ID; // Patient ID
        int age; // Patient age
        vector<Appointment> medicalHistory; // Medical history (list of appointments)

    public:
        // Constructor for patient object
        Patients(string _name, string _ID, int _age, vector<Appointment> _medicalHistory): 
        name(_name), ID(_ID), age(_age), medicalHistory(_medicalHistory){}

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

// Class Chronic Patient
class ChronicPatients: public Patients{
    private:
        string conditionType; // Type of chronic disease
        string lastCheckUpDate; // Last check-up date
        string frequency; // Check-up frequency
        
    public:
        // Constructor for chronic patient object
        ChronicPatients(string _name, string _ID, int _age, vector<Appointment> _medicalHistory, string _conditionType, string _lastCheckUpDate, string _frequency)
        : Patients(_name, _ID, _age, _medicalHistory), conditionType(_conditionType), lastCheckUpDate(_lastCheckUpDate), frequency(_frequency) {}

        // Display chronic patient information
        void displayPatientInfo() override {
            Patients::displayPatientInfo(); // Call parent class function
            cout << "Condition Type: " << conditionType << endl;
            cout << "Last Check-up Date: " << lastCheckUpDate << endl;
        }
        
        // Schedule appointment for chronic patient
        void scheduleAppointment() override {
            Patients::scheduleAppointment(); // Call parent class function
            
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

// Class Doctor
class Doctors{
    private:
        string name; // Doctor name
        string ID; // Doctor ID
        string specialty; // Specialty
        vector<Appointment> assignedAppointments; // List of assigned appointments

    public:
        // Constructor for doctor object
        Doctors(string _name, string _ID, string _specialty, vector<Appointment> _assignedAppointments): 
        name(_name), ID(_ID), specialty(_specialty), assignedAppointments(_assignedAppointments){}
        
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

    // Display room information
    void displayRoomInfo() {
        cout << "Room Number: " << roomNumber << endl;
        cout << "Department: " << department << endl;
        cout << "Available: ";
        if (available) cout << "Yes\n";
        else cout << "No\n"; 
    }
    
    // Update room status
    void setAvailability(bool status) {
        available = status;
    }
};

int main() {
    // Create a list of clinic rooms
    vector<Room> clinicRooms = {
        Room("101", "Cardiology", true),
        Room("102", "Neurology", false),
        Room("103", "Pediatrics", true),
        Room("104", "General Medicine", true)
    };

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
            // Create patient 1 with medical history
            vector<Appointment> history1;
            history1.push_back(Appointment("7/9/2025", "10:00", "Fever", "Completed"));
            history1.push_back(Appointment("8/9/2025", "09:00", "Flu", "Scheduled"));
            history1.push_back(Appointment("14/8/2025", "15:00", "Headache", "Completed"));
            Patients patient1("Nguyen Van An", "P001", 25, history1);

            // Display patient 1 info
            patient1.displayPatientInfo();

            // Function menu
            cout << "Choose function: ";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. View room\n";
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

            // Create patient 2 with medical history
            vector<Appointment> history2;
            history2.push_back(Appointment("6/9/2025", "14:00", "Cough", "Scheduled"));
            history2.push_back(Appointment("10/9/2025", "11:00", "Fever", "Completed"));
            history2.push_back(Appointment("12/9/2025", "16:00", "Back Pain", "Scheduled"));
            Patients patient2("Le Thi Binh", "P002", 30, history2);

            // Display patient 2 info
            patient2.displayPatientInfo();
            
            // Function menu
            cout << "Choose function: ";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. View room\n";
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
            // Create chronic patient 1 with medical history
            vector<Appointment> history1;
            history1.push_back(Appointment("20/8/2025", "09:00", "Diabetes Checkup", "Completed"));
            history1.push_back(Appointment("22/8/2025", "10:30", "Blood Test", "Completed"));
            history1.push_back(Appointment("25/8/2025", "08:30", "Eye Check", "Scheduled"));
            ChronicPatients chronicPatient1("Tran Van Cuong", "C001", 50, history1, "Diabetes", "20/8/2025", "Every 3 months");
            
            // Display chronic patient 1 info
            chronicPatient1.displayPatientInfo();
            
            // Function menu
            cout << "Choose function: ";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. Check regular health check-up frequency\n";
            cout << "5. View room\n";
            int n;
            cin >> n;

            switch (n) {
                case 1: {
                    chronicPatient1.scheduleAppointment();
                    chronicPatient1.viewMedicalHistory();
                    break;
                }
                
                case 2: {
                    chronicPatient1.viewMedicalHistory();
                    break;
                }

                case 3: {
                    chronicPatient1.updateMedicalHistory();
                    chronicPatient1.viewMedicalHistory();
                    break;
                }

                case 4: {
                    chronicPatient1.checkFrequency();
                    break;
                }

                case 5: {
                    for (int i = 0; i < clinicRooms.size(); i++){
                        clinicRooms[i].displayRoomInfo();
                        cout << endl;
                    }
                    break;
                }

                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            // Create chronic patient 2 with medical history
            vector<Appointment> history2;
            history2.push_back(Appointment("10/7/2025", "15:00", "Hypertension Checkup", "Completed"));
            history2.push_back(Appointment("12/7/2025", "09:00", "ECG Test", "Completed"));
            history2.push_back(Appointment("18/7/2025", "13:30", "Kidney Function Test", "Scheduled"));
            ChronicPatients chronicPatient2("Pham Thi Duong", "C002", 60, history2, "Hypertension", "10/7/2025", "Every 6 months");

            // Choose function for chronic patient 2
            cout << "Choose function: ";
            cout << "1. Schedule appointment\n";
            cout << "2. View medical history\n";
            cout << "3. Update medical history\n";
            cout << "4. Check regular health check-up frequency\n";
            cout << "5. View room\n";
            cin >> n;

            switch (n) {
                case 1: {
                    chronicPatient2.scheduleAppointment();
                    chronicPatient2.viewMedicalHistory();
                    break;
                }
                
                case 2: {
                    chronicPatient2.viewMedicalHistory();
                    break;
                }

                case 3: {
                    chronicPatient2.updateMedicalHistory();
                    chronicPatient2.viewMedicalHistory();
                    break;
                }

                case 4: {
                    chronicPatient2.checkFrequency();
                    break;
                }

                case 5: {
                    for (int i = 0; i < clinicRooms.size(); i++){
                        clinicRooms[i].displayRoomInfo();
                        cout << endl;
                    }
                    break;
                }

                default: {
                    cout << "Invalid\n";
                    break;
                }
            }
            break;
        }

        // Doctor
        case 3: { 
            // Create doctor 1 with assigned appointments
            vector<Appointment> doctorApp1;
            doctorApp1.push_back(Appointment("15/8/2025", "10:00", "Fever", "Completed"));
            doctorApp1.push_back(Appointment("16/8/2025", "11:00", "Allergy", "Scheduled"));
            doctorApp1.push_back(Appointment("17/8/2025", "09:30", "Stomach Ache", "Completed"));
            Doctors doctor1("Tran Van Anh", "D001", "Cardiology", doctorApp1);

            // Display doctor 1 info
            doctor1.displayDoctorInfo();
            
            // Function menu
            cout << "Choose function: ";
            cout << "1. View your appointment\n";
            cout << "2. Update appointment status\n";
            cout << "3. Update room status\n";
            int n;
            cin >> n;

            switch (n) {
                case 1: { // View assigned appointments
                    doctor1.viewAssignedAppointments();
                    break;
                }
                
                case 2: { // Update appointment status
                    doctor1.updateStatus(); 
                    break;
                }

                case 3: { // Update clinic room availability
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

                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            // Create doctor 2 with assigned appointments
            vector<Appointment> doctorApp2;
            doctorApp2.push_back(Appointment("19/8/2025", "14:00", "Cough", "Scheduled"));
            doctorApp2.push_back(Appointment("20/8/2025", "15:00", "Fever", "Completed"));
            doctorApp2.push_back(Appointment("21/8/2025", "10:30", "General Checkup", "Scheduled"));
            Doctors doctor2("Le Thi Hoa", "D002", "Pediatrics", doctorApp2);

            // Display doctor 2 info
            doctor2.displayDoctorInfo();

            // Function menu
            cout << "Choose function: ";
            cout << "1. View your appointment\n";
            cout << "2. Update appointment status\n";
            cout << "3. Update room status\n";
            cin >> n;

            switch (n) {
                case 1: {
                    doctor2.viewAssignedAppointments();
                    break;
                }
                
                case 2: {
                    doctor2.updateStatus(); 
                    break;
                }

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

                default: {
                    cout << "Invalid\n";
                    break;
                }
            }

            break;
        }

        default:
            cout << "Invalid\n";
            break;
    }
}
