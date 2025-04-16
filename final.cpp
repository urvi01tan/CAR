#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
#include <list>
#include <limits>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <climits>

using namespace std;

class Waitlist
{
    queue<string> customerQueue;

public:
    void enqueue(const string &customer)
    {
        customerQueue.push(customer);
    }

    string dequeue()
    {
        if (!customerQueue.empty())
        {
            string customer = customerQueue.front();
            customerQueue.pop();
            return customer;
        }
        return "Waitlist is empty.";
    }

    void displayWaitlist()
    {
        queue<string> temp = customerQueue;
        if (temp.empty())
        {
            cout << "Waitlist is empty." << endl;
            return;
        }
        cout << "Waitlist:" << endl;
        while (!temp.empty())
        {
            cout << temp.front() << endl;
            temp.pop();
        }
    }

    bool isEmpty() const
    {
        return customerQueue.empty();
    }
};

class ActionStack
{
    stack<string> actions;

public:
    void pushAction(const string &action)
    {
        actions.push(action);
    }

    string popAction()
    {
        if (!actions.empty())
        {
            string action = actions.top();
            actions.pop();
            return action;
        }
        return "No actions to undo.";
    }

    void displayActions()
    {
        stack<string> temp = actions;
        if (temp.empty())
        {
            cout << "No actions recorded." << endl;
            return;
        }
        cout << "Action History:" << endl;
        while (!temp.empty())
        {
            cout << temp.top() << endl;
            temp.pop();
        }
    }

    bool isEmpty() const
    {
        return actions.empty();
    }
};

class Graph
{
    unordered_map<string, vector<pair<string, int>>> adjacencyList;

public:
    void addEdge(const string &from, const string &to, int weight)
    {
        adjacencyList[from].emplace_back(to, weight);
        adjacencyList[to].emplace_back(from, weight);
    }

    void displayLocations()
    {
        cout << "Rental Locations and Distances:" << endl;
        for (const auto &location : adjacencyList)
        {
            cout << location.first << " -> ";
            for (const auto &neighbor : location.second)
            {
                cout << neighbor.first << " (" << neighbor.second << " units), ";
            }
            cout << endl;
        }
    }

    int shortestPath(const string &start, const string &end)
    {
        unordered_map<string, int> distances;
        for (const auto &node : adjacencyList)
        {
            distances[node.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            auto top = pq.top();
            int currentDistance = top.first;
            string currentNode = top.second;
            pq.pop();

            if (currentNode == end)
                return currentDistance;

            for (const auto &neighbor : adjacencyList[currentNode])
            {
                string nextNode = neighbor.first;
                int weight = neighbor.second;
                int distance = currentDistance + weight;

                if (distance < distances[nextNode])
                {
                    distances[nextNode] = distance;
                    pq.push({distance, nextNode});
                }
            }
        }
        return -1;
    }
    void findShortestPath(const string &source, const string &destination)
    {
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;

        for (const auto &node : adjacencyList)
        {
            distances[node.first] = INT_MAX;
        }
        distances[source] = 0;
        previous[source] = ""; 

        pq.push({0, source});

        while (!pq.empty())
        {
            pair<int, string> top = pq.top();
            int currentDist = top.first;
            string currentNode = top.second;
            pq.pop();

            if (currentDist > distances[currentNode])
                continue;

            for (const auto &neighborPair : adjacencyList[currentNode])
            {
                string neighbor = neighborPair.first;
                int weight = neighborPair.second;
                int newDist = currentDist + weight;

                if (newDist < distances[neighbor])
                {
                    distances[neighbor] = newDist;
                    previous[neighbor] = currentNode;
                    pq.push({newDist, neighbor});
                }
            }
        }

        if (distances[destination] == INT_MAX)
        {
            cout << "No path found from " << source << " to " << destination << "!\n";
        }
        else
        {
            cout << "Shortest path from " << source << " to " << destination << ":\n";

            stack<string> path;
            for (string at = destination; at != ""; at = previous[at])
            {
                path.push(at);
            }

            while (!path.empty())
            {
                cout << path.top();
                path.pop();
                if (!path.empty())
                    cout << " -> ";
            }
            cout << "\nTotal Distance: " << distances[destination] << " km\n";
        }
    }
};

class BookingHistory
{
    struct Node
    {
        string bookingDetails;
        Node *next;
        Node(const string &details) : bookingDetails(details), next(nullptr) {}
    };

    Node *head;

public:
    BookingHistory() : head(nullptr) {}

    void addBooking(const string &details)
    {
        Node *newNode = new Node(details);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    void displayHistory() const
    {
        Node *current = head;
        if (!current)
        {
            cout << "No booking history available." << endl;
            return;
        }
        cout << "Booking History:" << endl;
        while (current)
        {
            cout << current->bookingDetails << endl;
            current = current->next;
        }
    }

    ~BookingHistory()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class VehicleTree
{
    struct TreeNode
    {
        int id;
        string vehicleDetails;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int vehicleId, const string &details) : id(vehicleId), vehicleDetails(details), left(nullptr), right(nullptr) {}
    };

    TreeNode *root;

    TreeNode *insert(TreeNode *node, int id, const string &details)
    {
        if (!node)
            return new TreeNode(id, details);
        if (id < node->id)
            node->left = insert(node->left, id, details);
        else if (id > node->id)
            node->right = insert(node->right, id, details);
        return node;
    }

    void inOrder(TreeNode *node) const
    {
        if (!node)
            return;
        inOrder(node->left);
        cout << "ID: " << node->id << ", Details: " << node->vehicleDetails << endl;
        inOrder(node->right);
    }

public:
    VehicleTree() : root(nullptr) {}

    void addVehicle(int id, const string &details)
    {
        root = insert(root, id, details);
    }

    void displayInventory() const
    {
        if (!root)
        {
            cout << "No vehicles in the inventory." << endl;
            return;
        }
        inOrder(root);
    }
};

class Car
{
public:
    int id;
    string category;
    string name;
    bool isAvailable;

    Car(int id, string category, string name)
    {
        this->id = id;
        this->category = category;
        this->name = name;
        this->isAvailable = true;
    }
};

class Customer
{
public:
    string name;
    string license;
    string aadhar;
    string mobileNumber;

    Customer(string name, string license, string aadhar, string mobileNumber)
    {
        this->name = name;
        this->license = license;
        this->aadhar = aadhar;
        this->mobileNumber = mobileNumber;
    }
};
struct RentalCompany
{
    string name;
    string address;
    string city;
    string pincode;
};

void printNearbyRentalCompanies(string userCity, string pincode, vector<RentalCompany> &companies)
{
    cout << "\n--- Nearby Rental Companies ---\n";
    bool foundNearby = false;

    for (const auto &company : companies)
    {
        if (company.city == userCity && company.pincode == pincode)
        {
            foundNearby = true;
            cout << "Company Name: " << company.name << endl;
            cout << "Address: " << company.address << endl;
            cout << "City: " << company.city << ", pincode: " << company.pincode << endl;
            cout << "-------------------------------\n";
        }
    }

    if (!foundNearby)
    {
        cout << "No rental companies found in your city and district.\n";
    }
}

class CarRentalSystem
{
private:
    vector<Car> cars;
    vector<Customer> customers;

public:
    CarRentalSystem()
    {
        cars.push_back(Car(1, "SUV", "Toyota Fortuner"));
        cars.push_back(Car(2, "Sedan", "Honda City"));
        cars.push_back(Car(3, "Hatchback", "Maruti Swift"));
        cars.push_back(Car(4, "SUV", "Hyundai Creta"));
        cars.push_back(Car(5, "Sedan", "Tata Tiago"));
        cars.push_back(Car(6, "Hatchback", "Hyundai i20"));
        cars.push_back(Car(7, "SUV", "Mahindra Scorpio"));
        cars.push_back(Car(8, "Sedan", "Maruti Suzuki Swift"));
        cars.push_back(Car(9, "Hatchback", "Ford Figo"));
        cars.push_back(Car(10, "SUV", "Tata Nexon"));
        cars.push_back(Car(11, "Sedan", "Toyota Corolla"));
        cars.push_back(Car(12, "SUV", "Mahindra Thar"));
        cars.push_back(Car(13, "Hatchback", "Renault Kwid"));
        cars.push_back(Car(14, "SUV", "Kia Seltos"));
        cars.push_back(Car(15, "SUV", "Skoda Kushaq"));
        cars.push_back(Car(16, "Sedan", "BMW 3 Series"));
        cars.push_back(Car(17, "Hatchback", "Volkswagen Polo"));
        cars.push_back(Car(18, "SUV", "Nissan X-Trail"));
        cars.push_back(Car(19, "Sedan", "Audi A4"));
        cars.push_back(Car(20, "SUV", "Jeep Compass"));
        cars.push_back(Car(21, "SUV", "Ford Endeavour"));
        cars.push_back(Car(22, "Sedan", "Mercedes-Benz C-Class"));
        cars.push_back(Car(23, "Hatchback", "Suzuki Baleno"));
        cars.push_back(Car(24, "SUV", "Land Rover Range Rover"));
        cars.push_back(Car(25, "Sedan", "Hyundai Elantra"));
        cars.push_back(Car(26, "Hatchback", "Honda Jazz"));
        cars.push_back(Car(27, "SUV", "Volkswagen Tiguan"));
        cars.push_back(Car(28, "Sedan", "Jaguar XF"));
        cars.push_back(Car(29, "Hatchback", "Chevrolet Spark"));
        cars.push_back(Car(30, "SUV", "BMW X5"));
        cars.push_back(Car(31, "Sedan", "Audi Q5"));
        cars.push_back(Car(32, "Hatchback", "Maruti Celerio"));
        cars.push_back(Car(33, "SUV", "Toyota Land Cruiser"));
        cars.push_back(Car(34, "Sedan", "Skoda Superb"));
        cars.push_back(Car(35, "Hatchback", "Tata Altroz"));
        cars.push_back(Car(36, "SUV", "Mahindra XUV300"));
        cars.push_back(Car(37, "Sedan", "Honda Accord"));
        cars.push_back(Car(38, "Hatchback", "Ford Fiesta"));
        cars.push_back(Car(39, "SUV", "Jeep Wrangler"));
        cars.push_back(Car(40, "Sedan", "Mercedes-Benz E-Class"));
        cars.push_back(Car(41, "SUV", "Porsche Cayenne"));
        cars.push_back(Car(42, "Hatchback", "Renault Triber"));
        cars.push_back(Car(43, "Sedan", "Volvo S90"));
        cars.push_back(Car(44, "SUV", "Tata Harrier"));
        cars.push_back(Car(45, "Sedan", "Honda City ZX"));
        cars.push_back(Car(46, "SUV", "Hyundai Tucson"));
        cars.push_back(Car(47, "Hatchback", "Nissan Micra"));
        cars.push_back(Car(48, "SUV", "Audi Q7"));
        cars.push_back(Car(49, "Sedan", "BMW 5 Series"));
        cars.push_back(Car(50, "SUV", "Kia Sonet"));
        cars.push_back(Car(51, "Sedan", "Chevrolet Cruze"));
        cars.push_back(Car(52, "Hatchback", "Datsun Redi-Go"));
        cars.push_back(Car(53, "SUV", "Renault Duster"));
        cars.push_back(Car(54, "Sedan", "Toyota Camry"));
        cars.push_back(Car(55, "SUV", "Nissan Patrol"));
        cars.push_back(Car(56, "Hatchback", "Suzuki Wagon R"));
        cars.push_back(Car(57, "SUV", "MG Hector"));
        cars.push_back(Car(58, "Sedan", "Lexus ES"));
        cars.push_back(Car(59, "SUV", "Honda CR-V"));
        cars.push_back(Car(60, "Hatchback", "Tata Nano"));
    }

    void calculateRentalPrice(int carId, string rentalType, int hoursOrDays)
    {
        for (Car &car : cars)
        {
            if (car.id == carId)
            {
                int price = 0;

                if (car.category == "SUV")
                {
                    if (rentalType == "day")
                    {
                        price = 10000 * hoursOrDays;
                    }
                    else if (rentalType == "hour")
                    {
                        price = 500 * hoursOrDays;
                    }
                }

                else if (car.category == "Sedan")
                {
                    if (rentalType == "day")
                    {
                        price = 5000 * hoursOrDays;
                    }
                    else if (rentalType == "hour")
                    {
                        price = 300 * hoursOrDays;
                    }
                }

                else if (car.category == "Hatchback")
                {
                    if (rentalType == "day")
                    {
                        price = 4000 * hoursOrDays;
                    }
                    else if (rentalType == "hour")
                    {
                        price = 250 * hoursOrDays;
                    }
                }

                cout << "Car Name: " << car.name << endl;
                cout << "Category: " << car.category << endl;
                cout << "Rental Type: " << rentalType << endl;
                cout << "Total Rental Price: " << price << " INR" << endl;
                return;
            }
        }
        cout << "Car ID not found!\n";
    }

    void loginCustomer()
    {
        string name, license;
        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your license: ";
        getline(cin, license);

        ifstream inFile("customers.txt");
        if (inFile)
        {
            string line;
            bool found = false;
            while (getline(inFile, line))
            {
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                string fileName = line.substr(0, pos1);
                string fileLicense = line.substr(pos1 + 1, pos2 - pos1 - 1);

                if (fileName == name && fileLicense == license)
                {
                    cout << "Login successful! Welcome, " << name << ".\n";
                    found = true;
                    break;
                }
            }
            inFile.close();

            if (!found)
            {
                cout << "Login failed. Customer not found.\n";
            }
        }
        else
        {
            cout << "Error opening customer data file.\n";
        }
    }

    void displayCars(string category)
    {
        cout << "\nAvailable cars in category '" << category << "':\n";
        for (Car &car : cars)
        {
            if (car.category == category && car.isAvailable)
            {
                cout << "ID: " << car.id << ", Name: " << car.name << endl;
            }
        }
    }

    void registerCustomer()
    {
        string name, license, aadhar, mobileNumber;
        cout << "\nEnter customer details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "License: ";
        getline(cin, license);
        cout << "Aadhar: ";
        getline(cin, aadhar);
        cout << "Mobile Number: ";
        getline(cin, mobileNumber);

        customers.push_back(Customer(name, license, aadhar, mobileNumber));
        cout << "Customer registered successfully!\n";
        ofstream outFile("customers.txt", ios::app);
        if (outFile)
        {
            outFile << name << "," << license << "," << aadhar << "," << mobileNumber << "\n";
            outFile.close();
            cout << "Customer registered successfully and saved to file!\n";
        }
        else
        {
            cout << "Error saving customer data to file.\n";
        }
    }

    void bookCar()
    {

        string rentalType;
        int hoursOrDays;
        int carId;
        string customerName;

        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, customerName);
        cout << "Enter Car ID to book: ";
        cin >> carId;

        cout << "Do you want to rent the car for a day or hour? (Enter 'day' or 'hour'): ";
        cin >> rentalType;

        cout << "How many " << (rentalType == "day" ? "days" : "hours") << " do you want to rent the car for? ";
        cin >> hoursOrDays;

        calculateRentalPrice(carId, rentalType, hoursOrDays);

        for (Car &car : cars)
        {
            if (car.id == carId && car.isAvailable)
            {
                car.isAvailable = false;
                cout << "Car '" << car.name << "' booked successfully by " << customerName << "!\n";
                return;
            }
        }
        cout << "Car not available or invalid ID!\n";
    }

    void returnCar()
    {
        int carId;
        cout << "\nEnter Car ID to return: ";
        cin >> carId;

        for (Car &car : cars)
        {
            if (car.id == carId && !car.isAvailable)
            {
                car.isAvailable = true;
                cout << "Car '" << car.name << "' returned successfully!\n";
                return;
            }
        }
        cout << "Invalid Car ID or the car is already available!\n";
    }

    void usageDetails()
    {
        int carId;
        cout << "\nEnter Car ID to check details: ";
        cin >> carId;

        for (Car &car : cars)
        {
            if (car.id == carId)
            {
                cout << "Car Name: " << car.name << ", Category: " << car.category
                     << ", Availability: " << (car.isAvailable ? "Available" : "Not Available") << endl;
                return;
            }
        }
        cout << "Car not found!\n";
    }
};

int main()
{
    Waitlist waitlist;
    ActionStack actions;
    Graph rentalLocations;
    BookingHistory history;
    VehicleTree inventory;

    int c;
    cout << "enter whether you are owner or a customer(1 for owner and 2 for customer):";
    cin >> c;
    switch (c)
    {
    case 1:
    {
        int choice;
        do
        {
            cout << "\n--- Car Rental Management ---\n";
            cout << "1. Add Vehicle\n";
            cout << "2. View Vehicle Inventory\n";
            cout << "3. Add Rental Location\n";
            cout << "4. View Rental Locations\n";
            cout << "5. Add Booking History\n";
            cout << "6. View Booking History\n";
            cout << "7. Manage Waitlist\n";
            cout << "8. Undo Last Action\n";
            cout << "9. Find Shortest Distance Between Locations\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                int id;
                string details;
                cout << "Enter Vehicle ID: ";
                cin >> id;

                cout << "Enter Vehicle Details: ";
                cin.ignore();
                getline(cin, details);
                inventory.addVehicle(id, details);
                actions.pushAction("Added Vehicle ID: " + to_string(id));
                break;
            }
            case 2:
                inventory.displayInventory();
                break;
            case 3:
            {
                string from, to;
                int distance;
                cout << "Enter Starting Location: ";
                cin >> from;
                cout << "Enter Destination Location: ";
                cin >> to;
                cout << "Enter Distance: ";
                cin >> distance;
                rentalLocations.addEdge(from, to, distance);
                actions.pushAction("Added Rental Location: " + from + " -> " + to);
                break;
            }
            case 4:
                rentalLocations.displayLocations();
                break;
            case 5:
            {
                string booking;
                cout << "Enter Booking Details: ";
                cin.ignore();
                getline(cin, booking);
                history.addBooking(booking);
                actions.pushAction("Added Booking: " + booking);
                break;
            }
            case 6:
                history.displayHistory();
                break;
            case 7:
            {
                cout << "1. Add Customer to Waitlist\n";
                cout << "2. Serve Next Customer\n";
                cout << "3. View Waitlist\n";
                int subChoice;
                cin >> subChoice;
                if (subChoice == 1)
                {
                    string customer;
                    cout << "Enter Customer Name: ";
                    cin.ignore();
                    getline(cin, customer);
                    waitlist.enqueue(customer);
                    actions.pushAction("Added to Waitlist: " + customer);
                }
                else if (subChoice == 2)
                {
                    cout << "Serving Customer: " << waitlist.dequeue() << endl;
                }
                else if (subChoice == 3)
                {
                    waitlist.displayWaitlist();
                }
                break;
            }
            case 8:
                cout << "Undoing Action: " << actions.popAction() << endl;
                break;
            case 9:
            {
                string from, to;
                cout << "Enter Starting Location: ";
                cin >> from;
                cout << "Enter Destination Location: ";
                cin >> to;
                int distance = rentalLocations.shortestPath(from, to);
                if (distance >= 0)
                {
                    cout << "Shortest distance between " << from << " and " << to << " is: " << distance << " km.\n";
                }
                else
                {
                    cout << "Path between " << from << " and " << to << " not found.\n";
                }
                break;
            }
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 0);
        break;
    }

    case 2:

    {
        CarRentalSystem carRentalSystem;
        int carId;
        string rentalType;
        int hoursOrDays;
        vector<RentalCompany> rentalCompanies = {
            {"Mumbai Car Rentals", "123 Marine Drive, Mumbai", "Mumbai", "400020"},
            {"Delhi Wheels", "456 Connaught Place, New Delhi", "New Delhi", "110001"},
            {"Bangalore Speedy Rentals", "789 MG Road, Bengaluru", "Bengaluru", "560001"},
            {"Hyderabad Quick Rentals", "101 Banjara Hills, Hyderabad", "Hyderabad", "500034"},
            {"Chennai CityX Rentals", "202 Anna Salai, Chennai", "Chennai", "600002"},
            {"Kolkata Prime Rentals", "303 Park Street, Kolkata", "Kolkata", "700016"},
            {"Pune Drive Rentals", "404 FC Road, Pune", "Pune", "411005"},
            {"Ahmedabad Auto Rentals", "505 CG Road, Ahmedabad", "Ahmedabad", "380009"},
            {"Jaipur PinkCity Rentals", "606 MI Road, Jaipur", "Jaipur", "302001"},
            {"Lucknow Urban Rentals", "707 Hazratganj, Lucknow", "Lucknow", "226001"},
            {"Chandigarh City Rentals", "808 Sector 17, Chandigarh", "Chandigarh", "160017"},
            {"Indore Fast Rentals", "909 MG Road, Indore", "Indore", "452001"},
            {"Bhopal Eco Rentals", "101 New Market, Bhopal", "Bhopal", "462003"},
            {"Thiruvananthapuram Rentals", "202 MG Road, Thiruvananthapuram", "Thiruvananthapuram", "695001"},
            {"Guwahati Speed Rentals", "303 GS Road, Guwahati", "Guwahati", "781005"},
            {"Nagpur Orange Rentals", "404 Civil Lines, Nagpur", "Nagpur", "440001"},
            {"Visakhapatnam Rentals", "505 Beach Road, Visakhapatnam", "Visakhapatnam", "530001"},
            {"Patna Smart Rentals", "606 Gandhi Maidan, Patna", "Patna", "800001"},
            {"Vadodara Car Rentals", "707 Alkapuri, Vadodara", "Vadodara", "390007"},
            {"Surat Rentals", "808 Ring Road, Surat", "Surat", "395003"},
            {"Kanpur Ride Rentals", "909 Mall Road, Kanpur", "Kanpur", "208001"},
            {"Coimbatore Fast Rentals", "101 Avinashi Road, Coimbatore", "Coimbatore", "641018"},
            {"Madurai Quick Rentals", "202 Meenakshi Amman Temple Road, Madurai", "Madurai", "625001"},
            {"Ranchi Drive Rentals", "303 Main Road, Ranchi", "Ranchi", "834001"},
            {"Raipur Rentals", "404 Pandri, Raipur", "Raipur", "492001"},
            {"Mysuru Rentals", "505 Devaraja Market, Mysuru", "Mysuru", "570001"},
            {"Varanasi Rentals", "606 Assi Ghat Road, Varanasi", "Varanasi", "221005"},
            {"Agra City Rentals", "707 Taj Road, Agra", "Agra", "282001"},
            {"Amritsar Rentals", "808 Golden Temple Road, Amritsar", "Amritsar", "143001"},
            {"Meerut Car Rentals", "909 Shastri Nagar, Meerut", "Meerut", "250001"}};
        cin.ignore();
        string userCity, pincode;
        cout << "Enter your city: ";
        getline(cin, userCity);
        cout << "Enter its pincode: ";
        getline(cin, pincode);
        printNearbyRentalCompanies(userCity, pincode, rentalCompanies);
        CarRentalSystem system;
        int choice;

        do
        {
            cout << "\nCar Rental System Menu:";
            cout << "\n1. Display Cars by Category";
            cout << "\n2. Register Customer";
            cout << "\n3. Book Car";
            cout << "\n4. Return a Car";
            cout << "\n5.Car usage details";
            cout << "\n6.Login Customer";
            cout << "\n7.Exit.Thank You for Visiting";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string category;
                cout << "Enter car category (SUV/Sedan/Hatchback): ";
                cin >> category;
                system.displayCars(category);
                break;
            }
            case 2:
                system.registerCustomer();
                break;
            case 3:
                cout << "===============================================\n";
                cout << " Categories of Cars in our system are: \n";
                cout << " 1. SUV   | 2. Sedan   | 3. Hatchback\n";
                cout << "===============================================\n";
                Sleep(2000);

                cout << " Car Category    | Daily Wages      | Hourly Wages   \n";
                cout << "-------------------------------------------------------\n";

                cout << setw(16) << "SUV"
                     << setw(20) << "10,000 INR"
                     << setw(15) << "500 INR" << endl;

                cout << setw(16) << "Sedan"
                     << setw(20) << "5,000 INR"
                     << setw(15) << "300 INR" << endl;

                cout << setw(16) << "Hatchback"
                     << setw(20) << "4,000 INR"
                     << setw(15) << "250 INR" << endl;

                cout << "===============================================\n";
                Sleep(2000);
                system.bookCar();
                break;
            case 4:
                system.returnCar();
                break;
            case 5:
                system.usageDetails();
                break;
            case 6:
                system.loginCustomer();
                break;
            case 7:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 7);
        break;
    }
    default:
    {
        cout << "INVALID CHOICE";
        break;
    }
    }

    return 0;
}