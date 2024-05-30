#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Product
{
public:
    int Pid;
    string Pname;
    int stock;
    int price;
    int exp_month;
    int exp_year;
    Product* pnext;
};


class clistproduct {
public:
    Product* phead;
    Product* ptail;
    clistproduct() {
        phead = NULL;
        ptail = NULL;
    }
    ~clistproduct() {
        Product* temp = phead;
        while (phead != NULL) {
            phead = phead->pnext;
            temp->pnext = NULL;
            delete temp;
            temp = phead;
        }
    }
    void attach(Product* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }
};


class Customer {
public:
    int Cid;
    string cname;
    string pass;
    Customer* pnext;
};



class clistCustomer {
public:
    Customer* phead;
    Customer* ptail;
    clistCustomer() {
        phead = NULL;
        ptail = NULL;
    }
    void attach(Customer* pnn) {
        if (phead == NULL) {
            phead = ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }
    void Display() {
        Customer* pTrave = phead;
        while (pTrave != NULL) {
            std::cout << pTrave->Cid << " " << pTrave->cname << " " << pTrave->pass << " " << endl;
            pTrave = pTrave->pnext;
        }
    }

    int checkC(int id) {
        if (phead != NULL) {
            Customer* trav = phead;
            while (trav != NULL) {
                if (trav->Cid == id) {
                    return 1;
                }
                trav = trav->pnext;
            }
        }
        return 0;
    }

    void add(int cid, string cname) {
        Customer* newCustomer = new Customer;
        newCustomer->Cid = cid;
        newCustomer->cname = cname;
        newCustomer->pnext = NULL;

        if (phead == NULL) {
            phead = newCustomer;
            ptail = newCustomer;
        }
        else {
            ptail->pnext = newCustomer;
            ptail = newCustomer;
        }
    }
};



class Orders {
public:
    int Pid;
    int Cid;
    Orders* pnext;
};



class clistOrders {
public:
    Orders* phead;
    Orders* ptail;

    void add(int pid, int cid) {
        Orders* newOrder = new Orders;
        newOrder->Cid = cid;
        newOrder->Pid = pid;
        newOrder->pnext = NULL;

        if (phead == NULL) {
            phead = newOrder;
            ptail = newOrder;
        }
        else {
            ptail->pnext = newOrder;
            ptail = newOrder;
        }
    }

    clistOrders() {
        phead = NULL;
        ptail = NULL;
    }

    ~clistOrders() {
        Orders* temp = phead;
        while (phead != NULL) {
            phead = phead->pnext;
            temp->pnext = NULL;
            delete temp;
            temp = phead;
        }
    }

    void attach(Orders* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }

    void display() {
        Orders* trav = phead;
        while (trav != NULL) {
            std::cout << trav->Cid << "," << trav->Pid;
            std::cout << endl;
            trav = trav->pnext;
        }
    }
};



class Admin {
public:
    int Pid;
    string cname;
    string pass;
    Admin* pnext;
};



class clistAdmin {
public:
    Admin* phead;
    Admin* ptail;
    clistAdmin() {
        phead = NULL;
        ptail = NULL;
    }

    ~clistAdmin() {
        Admin* temp = phead;
        while (phead != NULL) {
            phead = phead->pnext;
            temp->pnext = NULL;
            delete temp;
            temp = phead;
        }
    }

    void attach(Admin* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }

    int checkA(int id, string name, string password) {
        if (phead != NULL) {
            Admin* trav = phead;
            while (trav != NULL) {
                if (trav->Pid == id && trav->cname == name && trav->pass == password) {
                    return 1;
                }
                trav = trav->pnext;
            }
        }
        return 0;
    }
};



void LetTheCustomerBuy(clistCustomer* cid, clistproduct* pro, clistOrders* lo) {
    std::cout << "Enter the customer id " << endl;
    int customerid;
    std::cin >> customerid;

    // Check if customer exists
    if (!cid->checkC(customerid)) {
        std::cout << "Customer not found. Enter customer name: ";
        string customerName;
        std::cin >> customerName;
        cid->add(customerid, customerName);

        // Save customer information to file
        ofstream customerFile("C:\\Users\\elhag\\OneDrive\\Desktop\\clistcustomer.txt");
        Customer* customerTrav = cid->phead;
        while (customerTrav != NULL) {
            customerFile << customerTrav->Cid << "," << customerTrav->cname << "," << customerTrav->pass << endl; 
            customerTrav = customerTrav->pnext;
        }
        customerFile.close();

        std::cout << "Customer added successfully!" << endl;
    }

    // Check if product exists
    std::cout << "Enter the Product ID and the Quantity" << endl;
    int Productid, Quantity;
    std::cin >> Productid >> Quantity;

    Product* pt = pro->phead;

    while (pt != NULL) {
        if (pt->Pid == Productid) {
            pt->stock -= Quantity;

            // Add order information
            lo->add(Productid, customerid);

            // Save order information to file
            ofstream orderFile("C:\\Users\\elhag\\OneDrive\\Desktop\\clistorder.txt");
            Orders* orderTrav = lo->phead;
            while (orderTrav != NULL) {
                orderFile << orderTrav->Cid << "," << orderTrav->Pid << endl;
                orderTrav = orderTrav->pnext;
            }
            orderFile.close();

            // Save product information to file
            ofstream productFile("C:\\Users\\elhag\\OneDrive\\Desktop\\clistproduct.txt");
            Product* productTrav = pro->phead;
            while (productTrav != NULL) {
                productFile << productTrav->Pid << "," << productTrav->Pname << "," << productTrav->stock
                    << "," << productTrav->price << "," << productTrav->exp_month << ","
                    << productTrav->exp_year << endl;
                productTrav = productTrav->pnext;
            }
            productFile.close();
        }
        pt = pt->pnext;
    }
}



void LetTheCustomerReturn(clistCustomer * cid, clistproduct * pro, clistOrders * ord) {
   std::cout << "Enter Customer ID" << endl;
    int customerid;
    std::cin >> customerid;

    // Check if customer exists
    if (!cid->checkC(customerid)) {
        std::cout << "Customer not found." << endl;
        return;
    }

    std::cout << "Enter the productID" << endl;
    int productID;
    std::cin >> productID;

    std::cout << "Enter the quantity to be returned" << endl;
    int Quantity;
    std::cin >> Quantity;

    // Check if order exists
    Orders* pt = ord->phead;
    Orders* ptd = NULL;

    while (pt != NULL) {
        if (pt->Cid == customerid && pt->Pid == productID) {
            // Check if product exists
            Product* currentProduct = pro->phead;
            while (currentProduct != NULL) {
                if (currentProduct->Pid == productID) {
                    currentProduct->stock += Quantity;
                    break; 
                }
                currentProduct = currentProduct->pnext;
            }

            // Remove order information
            if (ptd != NULL) {
                if (pt == ord->ptail) {
                    ptd->pnext = NULL;
                    ord->ptail = ptd;
                }
                else {
                    ptd->pnext = pt->pnext;
                    pt->pnext = NULL;
                }
            }
            else {
                ord->phead = pt->pnext;
                pt->pnext = NULL;
            }
            delete pt;

            // Save order information to file
            ofstream orderFile("C:\\Users\\elhag\\OneDrive\\Desktop\\clistorder.txt");
            Orders* orderTrav = ord->phead;
            while (orderTrav != NULL) {
                orderFile << orderTrav->Cid << "," << orderTrav->Pid << endl;
                orderTrav = orderTrav->pnext;
            }
            orderFile.close();

            // Save product information to file
            ofstream productFile("C:\\Users\\elhag\\OneDrive\\Desktop\\clistproduct.txt");
            Product* productTrav = pro->phead;
            while (productTrav != NULL) {
                productFile << productTrav->Pid << "," << productTrav->Pname << "," << productTrav->stock
                    << "," << productTrav->price << "," << productTrav->exp_month << ","
                    << productTrav->exp_year << endl;
                productTrav = productTrav->pnext;
            }
            productFile.close();

            std::cout << "Return processed successfully!" << endl;
            return;
        }
        pt = pt->pnext;
    }

    std::cout << "Order not found for Customer ID: " << customerid << " and Product ID: " << productID << endl;
}




void AdminSignIn(clistAdmin* ad, clistproduct* pro) {
    cout << "Enter the ID,Name and password" << endl;
    int ID;
    string Name, Password;
    std::cin >> ID >> Name >> Password;
    Admin* pt = ad->phead;
    Product* ptr = pro->phead;
    if (!ad->checkA(ID, Name, Password)) {
        cout << "Invalid" << endl;
    }
    else {
        cout << "Admin signed in " << endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
    }
}



void DisplayALL(clistproduct* ou)
{
    Product* ptr = ou->phead;

    while (ptr != NULL) {
        cout << "Product whose id is " << ptr->Pid << " has:" << endl;
        cout << "Product's Name is " << ptr->Pname << endl;
        cout << "Products Stock is " << ptr->stock << endl;
        cout << "Product's Price is " << ptr->price << endl;
        cout << "Product's Expiry date is " << ptr->exp_month << "\\" << ptr->exp_year << endl;
        cout << "-------------------------" << endl;

        ptr = ptr->pnext;
    }

}



void AdjustProduct(clistproduct* pro) {
    int productId;
    cout << "Enter the Product ID to adjust: ";
    cin >> productId;

    Product* ptr = pro->phead;

    while (ptr != NULL) {
        if (ptr->Pid == productId) {
            // Display current product information
            cout << "Current Product Information:" << endl;
            cout << "Product ID: " << ptr->Pid << endl;
            cout << "Product Name: " << ptr->Pname << endl;
            cout << "Current Stock: " << ptr->stock << endl;
            cout << "Current Price: " << ptr->price << endl;
            cout << "Current Expiry Date: " << ptr->exp_month << "\\" << ptr->exp_year << endl;

            // Allow admin to adjust stock and price
            cout << "Enter the new stock: ";
            cin >> ptr->stock;
            cout << "Enter the new price: ";
            cin >> ptr->price;

            // Save changes to the file
            ofstream file("C:\\Users\\elhag\\OneDrive\\Desktop\\clistproduct.txt");
            Product* ptrave = pro->phead;
            while (ptrave != NULL) {
                file << ptrave->Pid << "," << ptrave->Pname << "," << ptrave->stock << "," << ptrave->price << "," << ptrave->exp_month << "," << ptrave->exp_year << endl;
                ptrave = ptrave->pnext;
            }
            file.close();

            cout << "Product Adjusted Successfully!" << endl;
            break; 
        }
        ptr = ptr->pnext;
    }

    if (ptr == NULL) {
        cout << "Product not found with ID: " << productId << endl;
    }
}



void DeleteProduct(clistproduct* pro)
{
    int productId;
    cout << "Enter the Product ID to delete: ";
    cin >> productId;

    Product* current = pro->phead;
    Product* previous = NULL;

    while (current != NULL) {
        if (current->Pid == productId) {
            if (previous == NULL) {
                
                pro->phead = current->pnext;
            }
            else {
                
                previous->pnext = current->pnext;
            }

            ofstream file("C:\\Users\\elhag\\OneDrive\\Desktop\\clistproduct.txt");
            Product* ptrave = pro->phead;
            while (ptrave != NULL) {
                file << ptrave->Pid << "," << ptrave->Pname << "," << ptrave->stock << "," << ptrave->price << "," << ptrave->exp_month << "," << ptrave->exp_year << endl;
                ptrave = ptrave->pnext;
            }
            file.close();

           
            delete current;
            cout << "Product Deleted Successfully!" << endl;
            return; 
        }

        previous = current;
        current = current->pnext;
    }

    // Product not found
    cout << "Product not found with ID: " << productId << endl;
}




void AddNewProduct(clistproduct* pro) {
    
    int newProductId = pro->ptail->Pid + 1;

    
    Product* newProduct = new Product;
    newProduct->Pid = newProductId;

    cout << "Enter Product Name: ";
    cin >> newProduct->Pname;

    cout << "Enter Stock: ";
    cin >> newProduct->stock;

    cout << "Enter Price: ";
    cin >> newProduct->price;

    cout << "Enter Expiry Month: ";
    cin >> newProduct->exp_month;

    cout << "Enter Expiry Year: ";
    cin >> newProduct->exp_year;

    pro->attach(newProduct);

   
    ofstream file("C:\\Users\\elhag\\OneDrive\\Desktop\\clistproduct.txt");
    Product* ptrave = pro->phead;
    while (ptrave != NULL) {
        file << ptrave->Pid << "," << ptrave->Pname << "," << ptrave->stock << "," << ptrave->price << "," << ptrave->exp_month << "," << ptrave->exp_year << endl;
        ptrave = ptrave->pnext;
    }
    file.close();

    cout << "Product Added Successfully!" << endl;
}



void DisplayLowStockProducts(clistproduct* pro)
{
    int threshold;
    cout << "Enter the stock threshold: ";
    cin >> threshold;

    Product* ptrave = pro->phead;

    cout << "Products with stock less than " << threshold << ":" << endl;
    while (ptrave != NULL) {
        if (ptrave->stock < threshold) {
            cout << "Product ID: " << ptrave->Pid << endl;
            cout << "Product Name: " << ptrave->Pname << endl;
            cout << "Stock: " << ptrave->stock << endl;
            cout << "Price: " << ptrave->price << endl;
            cout << "Expiry Date: " << ptrave->exp_month << "/" << ptrave->exp_year << endl;
            cout << "----------------------" << endl;
        }
        ptrave = ptrave->pnext;
    }
}



int CountOrdersByCustomer(clistOrders* ord, int customerId) 
{
    int orderCount = 0;

    Orders* ptrav = ord->phead;

    while (ptrav != NULL) {
        if (ptrav->Cid == customerId) {
            orderCount++;
        }
        ptrav = ptrav->pnext;
    }

    return orderCount;
}

void DisplayOrdersByCustomer(clistOrders* ord)
{
    int customerId;
    cout << "Enter Customer ID: ";
    cin >> customerId;

    int orderCount = CountOrdersByCustomer(ord, customerId);

    cout << "Customer with ID " << customerId << " has placed " << orderCount << " order(s)." << endl;
}


int main() {
    ifstream file;
    clistproduct lp;

    ifstream file2;
    clistCustomer lc;

    ifstream file3;
    clistOrders lo;

    ifstream file4;
    clistAdmin la;

    file.open("C:\\Users\\elhag\\OneDrive\\Desktop\\clistproduct.txt");

    if (!file.is_open()) {
        cerr << "Error opening file: clistproduct.txt" << endl;
        return 1;
    }

    string x;
    while (getline(file, x)) 
    {
        string temp[6]; int it = 0;
        for (int i = 0; i < x.length(); i++) {
            if (x[i] == ',') {
                it++;
            }
            else {
                temp[it] += x[i];
            }
        }
        Product* pnn = new Product;
        pnn->Pid = stoi(temp[0]);
        pnn->Pname = temp[1];
        pnn->stock = stoi(temp[2]);
        pnn->price = stoi(temp[3]);
        pnn->exp_month = stoi(temp[4]);
        pnn->exp_year = stoi(temp[5]);
        pnn->pnext = NULL;
        lp.attach(pnn);
    }

    file.close();

    file2.open("C:\\Users\\elhag\\OneDrive\\Desktop\\clistcustomer.txt");


    if (!file2.is_open()) {
        cerr << "Error opening file: clistcustomer.txt" << endl;
        return 1;
    }

    string y;
    while (getline(file2, y)) 
    {
        string temp[3]; int it = 0;
        for (int i = 0; i < y.length(); i++) {
            if (y[i] == ',') {
                it++;
            }
            else {
                temp[it] += y[i];
            }
        }
        Customer* pnn2 = new Customer;
        pnn2->Cid = stoi(temp[0]);
        pnn2->cname = temp[1];
        pnn2->pass = temp[2];
        pnn2->pnext = NULL;
        lc.attach(pnn2);
    }

    file2.close();

    file3.open("C:\\Users\\elhag\\OneDrive\\Desktop\\clistorder.txt");
    if (!file3.is_open()) {
        cerr << "Error opening file: clistorder.txt" << endl;
        return 1;
    }

    string z;
    while (getline(file3, z)) 
    {
        string temp[2]; int it = 0;
        for (int i = 0; i < z.length(); i++) {
            if (z[i] == ',') {
                it++;
            }
            else {
                temp[it] += z[i];
            }
        }

        Orders* pnno = new Orders;
        pnno->Cid = stoi(temp[0]);
        pnno->Pid = stoi(temp[1]);
        pnno->pnext = NULL;
        lo.attach(pnno);
    }

    file3.close();

    file4.open("C:\\Users\\elhag\\OneDrive\\Desktop\\clistadmin.txt");
    if (!file4.is_open()) {
        cerr << "Error opening file: clistadmin.txt" << endl;
        return 1;
    }

    string w;
    while (getline(file4, w)) 
    {
        string temp[3]; int it = 0;
        for (int i = 0; i < w.length(); i++) {
            if (w[i] == ',') {
                it++;
            }
            else {
                temp[it] += w[i];
            }
        }

        Admin* pnno = new Admin;
        pnno->Pid = stoi(temp[0]);
        pnno->cname = temp[1];
        pnno->pass = temp[2];
        pnno->pnext = NULL;
        la.attach(pnno);
    }

    file4.close();

    int choice;
    while (true)
    {
        cout << "===============================" << endl;
        cout << "1. Buy" << endl;
        cout << "2. Return" << endl;
        cout << "3. Display Products with stock > 0" << endl;
        cout << "4. Display Products with stock < threshold" << endl;
        cout << "5. Adjust Product" << endl;
        cout << "6. Delete Product" << endl;
        cout << "7. Add New Product" << endl;
        cout << "8. Display Orders by Customer" << endl;
        cout << "9. Sign In as Admin" << endl;
        cout << "10. Display Products" << endl;
        
        cout << "0. Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 0:
            cout << "Exiting the program." << endl;
            return 0;
        
        case 1:
            LetTheCustomerBuy(&lc, &lp, &lo);
            break;
        case 2:
            LetTheCustomerReturn(&lc, &lp, &lo);
            break;
        case 3:
            DisplayALL(&lp);
            break;
        case 4:
            DisplayLowStockProducts(&lp);
            break;
        case 5:
            AdjustProduct(&lp);
            break;
        case 6:
            DeleteProduct(&lp);
            break;
        case 7:
            AddNewProduct(&lp);
            break;
        case 8:
            DisplayOrdersByCustomer(&lo);
            break;
        case 9:
            AdminSignIn(&la, &lp);
            break;
        case 10:
            DisplayALL(&lp);
            break;
        
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    
    return 0;
}