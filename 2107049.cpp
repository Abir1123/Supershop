#include <vector>
#include <string>
#include <iostream>

using namespace std;
class product;
class cart;
class customer;
class cashier;
class inventory;
class supershop;
class office;

class product{
    int id,quantity;
    double price;
    string name,category;
    bool availability;
public:
     product(){;}
     product(int id, double price, int quantity,string name,string category,bool availability){
            this->id=id;
            this->price=price;
            this->quantity=quantity;
            this->name=name;
            this->category=category;
            this->availability=availability;
        }
        void product_getter(){
            cout<<"Product ID: "<<this->id<<endl;
            cout<<"Product Name: "<<this->name<<endl;
            cout<<"Product Price: "<<this->price<<endl;
            cout<<"Product Quantity: "<<this->quantity<<endl;
            cout<<"Product Category: "<<this->category<<endl;
            cout<<"Product Availability: "<<((this->availability)?"Available":"Not Available")<<endl;
        }
        string get_name(){
            return name;
        }
void reset_quant(int i){
            quantity=i;
        }
        void add_stock(int i){
            quantity+=i;
        }
  void remove_stock(int i){
      quantity-=i;
  }
  void reset_price(double n){
      price=n;
      }
    friend class inventory;
    friend class cart;
    friend class cashier;
     friend void search_by_name(vector<product>,string,int*);
     friend void search_by_id(vector<product>,int,int*);
     friend void category_search(vector<product>);
 };

void search_by_name(vector<product>p,string s,int *n=NULL){
    int l=p.size();
    int i;
    int counter{0};
    for(i=0;i<l;i++){
          if(p.at(i).name==s){
          p.at(i).product_getter();
          counter++;
          break;
          }
     }
    if(counter==0)
    cout<<"Sorry, we have no such product.\n";
*n=i;
}
void search_by_id(vector<product>p,int d,int *n=NULL){
    int l=p.size();
     int i{0};
     int counter{0};
     for(;i<l;i++){
          if(p.at(i).id==d){
          p.at(i).product_getter();
         
          counter++;
           break;
          }
     }
if(counter==0)
    cout<<"Sorry, we have no such product.\n";
*n=i;
}
void category_search(vector<product>p){
    string c;
    cout<<"Enter your desired category:";
    cin>>c;
    int l=p.size();
    int counter{0};
for(int i{0};i<l;i++){
    if(p.at(i).category==c){
        p.at(i).product_getter();
        counter++;
    }
}
if(counter)
    cout<<endl<<"Here is all products within "<<c<<" category\n";
    else
        cout<<"We don't have "<<c<<" category available"<<endl;
}

class inventory{
    vector<product>products;
    int total_products;
    int total_avail_products;
public:
    inventory(){
        total_products=0;
    }
void add_product(int i,double p,int q,string n,string c,bool a){
    total_products++;
    product dummy(i,p,q,n,c,a);
    products.push_back(dummy);
    if(dummy.availability)
        total_avail_products++;
}
  
 void remove_product(int id){
  
  int i;
  search_by_id(products,id,&i);
             products.erase(products.begin()+i);
             cin.ignore();
             fflush(stdin);
             total_products--;
 }
 void show_all(){
    cout<<"________________________________________\v";
    cout<<"There are total "<<total_products<<" products in the shop\v"<<endl;
    for (int i = 0; i <total_products; i++) {
        cout<<endl;
        products[i].product_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
 }
 void show_avail(){
    cout<<"________________________________________\v";
    cout<<"There are "<<total_avail_products<<" products currently available in the shop\v"<<endl;
    for (int i = 0; i <total_products; i++) {
        if (products[i].availability== 1) {
            cout<<endl;
            products[i].product_getter();
            cout << endl;
        }
    }
    cout<<"________________________________________\v"<<endl;
 }
 bool if_avail(int id, int quantity) {
     int i;
   search_by_id(products,id,&i);
    if (products[i].id == id) {
            if (products[i].availability == 1) {
                if (products[i].quantity>= quantity) {
                    return true;
                }
            }
        }
    return false;
}
     
 friend void search_by_name(vector<product>,string,int*);
     friend void search_by_id(vector<product>,int,int*);
        friend void category_search(string);
        friend class cart;
        friend class supershop;
 };

class cart{
  vector<product>Cart;
  int tot_prod;
    double total_price;
public:
    cart(){
        tot_prod=0;
        total_price=0;
    }
void add_to_cart(inventory a,int id,int q,int *t=NULL){
    int l=a.products.size();
    int oq;
    for(int i{0};i<l;i++){
    if(a.products.at(i).id==id){
    oq=a.products.at(i).quantity;
    if(q<=oq){
     Cart.push_back(a.products.at(i));
        Cart.at(tot_prod).reset_quant(q);
        *t=i;
    }
    else{
        cout<<"\nInvalid operation\n";
    }
    tot_prod++;
    total_price+=q*a.products.at(i).price;
    }
}
}
void remove_from_cart(inventory a,int id,int q,int *t=NULL){
    int i,j;
    int oq;
    int l=Cart.size();
    search_by_id(a.products,id,&j);
    for(i=0;i<l;i++){
        if(Cart.at(i).id==id){
            
    oq=Cart.at(i).quantity;
    if(q<=oq){
       
       Cart.at(i).reset_quant(oq-q);
        
        *t=j;
    }
    else
       cout<<"\nInvalid operation\n";
    }
    }
}
void show_cart(){
     cout<<"________________________________________\v";
    cout<<"There are total "<<tot_prod<<" products in your cart\v"<<endl;
    for (int i = 0; i <tot_prod; i++) {
        cout<<endl;
        Cart.at(i).product_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}
double grand_total(){
    return total_price;
}
int total_product(){
    return tot_prod;
}
void removeall(){
        Cart.clear();
        tot_prod=0;
        total_price=0;
    }
friend void search_by_id(vector<product>,int,int*);
friend class cashier;

};

class customer{
     int id;
     bool exclusive;
    string name, address, contact_num, email, gender;
public:
    customer() { exclusive=0; }
    customer(int id, string name, string address, string contact_num, string email, string gender) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->contact_num = contact_num;
        this->email = email;
        this->gender = gender;
        this->exclusive=0;
    }
    string get_name() {
        return this->name;
    }
    string get_gender() {
        return this->gender;
    }
     int get_id(){
        return this->id;
    }
    bool exclusive_getter(){
        return this->exclusive;
    }
    void set_exlusive(){
        this->exclusive=true;
    }
    void cust_getter() {
        cout<<endl;
        cout << "Customer Id: " << id << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Customer address: " << address << endl;
        cout << "Customer Contact Number: " << contact_num << endl;
        cout << "Customer Email: " << email << endl;
        cout << "Customer Gender: " << gender << endl;
    }
};

class cashier {
    int id;
    string name;
public:
    cashier() { ; }
    cashier(int id, string name) {
        this->id = id;
        this->name = name;
    }
    void process_payment(cart&,customer&);
    string getname() {
        return this->name;
    }
     int getid(){
        return this->id;
    }
    void cashier_getter(){
        cout<<endl;
        cout << "Cashier ID: " << this->id << endl;
        cout << "Cashier Name: " << this->name << endl;
    }
};

void cashier::process_payment(cart& cart1, customer& customer1) {
    cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "|========================================SUPERSHOP PAYMENT RECEIPT========================================|" << endl;
    cout<<"---------------------------------------------------------------------------------------------------------------\v"<<endl;
    cout << "CONTACT INFO:\v"<<endl;
    customer1.cust_getter();
    cout << "==========================================================================================================\v" << endl;
    cout << "Cashier ID: " << id << endl;
    cout << "Cashier: " << name << endl;
    cout << "==========================================================================================================\v" << endl;
    cout << "SERIAL NO.               ITEM               QUANTITY               CATEGORY               PRICE\v";

    for (int i = 0; i < cart1.tot_prod; i++) {
        cout <<"    "<<(i + 1);
        cout<< "                  " << cart1.Cart[i].name;
        cout<< "               " << cart1.Cart[i].quantity;
        cout<< "                  " << cart1.Cart[i].category;
        cout<< "              " << cart1.Cart[i].price<< endl << endl;
    }
    cout << "TOTAL PRICE                                                                              " << cart1.grand_total() << endl << endl;
    cout << "VAT                                                                                      " << (cart1.grand_total() * 0.15) << endl << endl;
    cout << "__________________________________________________________________________________________________" << endl << endl;
    cout << "GRAND TOTAL                                                                              " << cart1.grand_total() + (cart1.grand_total() * 0.15) << "\v";
    cout << "\v";
    cout << "Thank you for choosing us " << ((customer1.get_gender() == "Male") ? " Sir" : " Madam") << ". Come visit us again\v";

    cout << "\v=======================SUPERSHOP MANAGEMENT SYSTEM BY REZUAN, ABIR & SARWAD====================================\v" << endl;
}
class office{
    vector<cashier>Cashier;
    int total_employees;
    public:
        office(){total_employees=0;}
        void add_cashier(const cashier&);
        void remove_cashier(int);
        void show_cashiers();
        cashier get_cashier(int);
};
cashier office::get_cashier(int id){
    for(int i = 0;i<total_employees;i++){
        if(Cashier[i].getid()==id){
            return Cashier[i];
        }
    }
    return Cashier[0];
}
void office::add_cashier(const cashier& c){
    Cashier.push_back(c);
    total_employees++;
}
void office::remove_cashier(int id){
    int i;
    for (i = 0; i < total_employees; i++) {
        if ((Cashier[i].getid())==id) {
            break;
        }
    }
    if(i>=total_employees){
        cout<<"There aren't any employee with that id here"<<endl;
    }
    else{
        auto it = Cashier.begin();
        it += i;
        Cashier.erase(it);
        total_employees--;
    }
}
void office::show_cashiers(){
    int n = Cashier.size();
    cout<<"________________________________________\v";
    cout<<"There are total "<<total_employees<<" employees in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<endl;
        Cashier[i].cashier_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}
class Database{
    vector<customer>Customers;
    int total_customers;
    public:
        Database(){total_customers=0;}
        void add_customers(const customer&);
        bool find_customers(int);
        customer& customer_getter(int);

};

void Database::add_customers(const customer& c){
    Customers.push_back(c);
    total_customers++;
}

bool Database::find_customers(int id){
    for(int i=0;i<total_customers;i++){
        if((Customers[i].get_id())==id){
            return true;
        }
    }
    return false;
}

customer& Database::customer_getter(int id){
    for(int i=0;i<total_customers;i++){
        if((Customers[i].get_id())==id){
            return Customers[i];
        }
    }
    return Customers[0];
}

class supershop {
    string password;
    inventory inventory1;
    cart cart1;
    office office1;
    Database database;
    bool runtime;
    int restock_id;
    cashier cashier1;
    customer customer1;
public:
    supershop(){
        cashier temp = cashier(1,"Abir");
        office1.add_cashier(temp);
        password="1234";
        runtime=0;
        restock_id=1000;
    }
    void start_shopping();
    void stock();
    void modeselect();
    void management();
};
void supershop::management(){
    int q=0;
    string pass;
    cout<<"===========================================================================\v"<<endl;
    cout<<"       ::::PLEASE ENTER THE PASSWORD TO VERIFY YOUR IDENTITY:::"<<endl<<endl<<endl;
    cout<<"Password: "<<endl;
    cin>>pass;
    if(pass==password){
        cout<<"\n\n\n\n";
        cout<<"           WELCOME TO THE SHOP, MANAGER. HOW WOULD YOU LIKE TO MANAGE THE SHOP TODAY?\v"<<endl;
        while(q!=12){
            cout<<"Choose a query::"<<endl<<endl;
            cout<<"1. Add a product"<<endl<<endl;
            cout<<"2. Remove a product"<<endl<<endl;
            cout<<"3. Show all products"<<endl<<endl;
            cout<<"4. search a product"<<endl<<endl;
            cout<<"5. Reset quantity of a product"<<endl<<endl;
            cout<<"6. Reset price of a product"<<endl<<endl;
            cout<<"7. Add stock to a product"<<endl<<endl;
            cout<<"8. Remove stock of a product"<<endl<<endl;
            cout<<"9. Recruit a cashier"<<endl<<endl;
            cout<<"10. Fire a cashier"<<endl<<endl;
            cout<<"11. Show all cashiers"<<endl<<endl;
            cout<<"12. Exit and Finalize changes"<<endl<<endl;
            cin>>q;
            switch(q){
                case 1:
                {
                    int n;
            int id, quantity;
            double price;
            string name, category;
            bool availability;
                    cout<<"\vHow many products do you want to add?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    while(n--){
                        cout<<"Please enter the id of the product"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        cout<<"Please enter the name of the product"<<endl<<endl;
                        cin>>name;
                        cout<<endl;
                        cout<<"Please enter the quantity of the added product"<<endl<<endl;
                        cin>>quantity;
                        cout<<endl;
                        cout<<"Please enter the price of the added product"<<endl<<endl;
                        cin>>price;
                        cout<<endl;
                        cout<<"Please enter the category of the added prdouct"<<endl<<endl;
                        cin>>category;
                        cout<<endl;
                        availability=(quantity>0)?true:false;
                        inventory1.add_product(id,price,quantity,name,category,availability);
                    }
                    
                }
                    break;
                case 2:
                {
                    int n,id;
                    cout<<"\vHow many products do you want to remove?\v"<<endl;
                    cin>>n;
                    while(n--){
                        cout<<"ID of the product you want to remove:";
                        cin>>id;
                        inventory1.remove_product(id);
                    }
                    
                }
                    break;
                case 3:
                    inventory1.show_all();
                    break;
                case 4:
                {
                    cout<<"Press 1 to search product id\n"<<"Press 2 to search product name\n";
int o;
cin>>o;
if(o==1){                    
                        int id;
                        cout<<"Enter the id you want to search:";
                        cin>>id;
                    search_by_id(inventory1.products,id,&id);
                    
}
else{
    cin.ignore();
    fflush(stdin);
    string s;
int i;
    cout<<"Enter the name you want to search:";
        getline(cin,s);
        search_by_name(inventory1.products,s,&i);
}
                }
                    break;
                     case 5:
                     {
                   int id,q,i;
                   cout<<"ID of the product:";
                   cin>>id;
                   cout<<"New quantity of the product:";
                   cin>>q;
                   search_by_id(inventory1.products,id,&i);
                    inventory1.products.at(i).reset_quant(q);
                     }
                    break;
                    case 6:
                    {
                   int id;
                   double p;
                   cout<<"ID of the product:";
                   cin>>id;
                   cout<<"New price of the product:";
                   cin>>p;
                   search_by_id(inventory1.products,id,&id);
                    inventory1.products.at(id).reset_price(p);
                     }
                    break;
                    case 7:
                    {
                   int id;
                   int q;
                   cout<<"ID of the product:";
                   cin>>id;
                   cout<<"increase of the product quantity:";
                   cin>>q;
                   search_by_id(inventory1.products,id,&id);
                    inventory1.products.at(id).add_stock(q);
                    
                    }
                    break;
                    case 8:
                    {
                   int id;
                   int q;
                   cout<<"ID of the product:";
                   cin>>id;
                   cout<<"decrease of the product quantity:";
                   cin>>q;
                    search_by_id(inventory1.products,id,&id);
                    inventory1.products.at(id).remove_stock(q);
                    
                    }
                    break;
                    case 9:
                    {
                        int n,id;
                        string name;
                    cout<<"\vHow many employees do you want to recruit?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the employee"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        cout<<"Please enter the name of the employee"<<endl<<endl;
                        cin>>name;
                        cout<<endl;
                        office1.add_cashier(cashier(id,name));
                    }
                    
                    }
                    break;
                case 10:
                {
                    int n,id;
                    cout<<"\vHow many employees do you want to fire?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the employee"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        office1.remove_cashier(id);
                    }
                    
                }
                    break;
                case 11:
                    office1.show_cashiers();
                    break;
                default:
                    cout<<"\vYOUR REQUESTS HAVE BEEN SUCCESSFULLY PROCESSED!!!\v";
                    break;
            }
        }
    }
    else{
        
        cout<<"                     YOU ARE NOT THE MANAGER!!!"<<endl;
        cout<<"                   MANAGEMENT SYSTEM IS EXITING...\v";
        return;
    }
}
void supershop::stock() {
    inventory1.add_product(1, 80,7, "Toothpaste", "Toiletries", 1);
    inventory1.add_product(2, 50,10,  "Soap", "Toiletries", 1);
    inventory1.add_product(3, 140, 8, "Shampoo", "Toiletries", 1);
    inventory1.add_product(4,  100,18,"Notebook", "Stationary", 1);
    inventory1.add_product(5, 10, 40, "Pens", "Stationary", 1);
    inventory1.add_product(6,250,  1, "Books", "Stationary", 1);
    inventory1.add_product(7, 400, 0, "Perfume", "Beauty", 0);
    inventory1.add_product(8, 4000, 3, "Fan", "Household", 1);
    inventory1.add_product(9, 1300, 5, "Bag", "Utilities", 1);
    inventory1.add_product(10, 90,  13,"Medicine", "Medical", 1);
}

void supershop::modeselect(){
    int n=0;
    while(n!=3){
        cout<<"\v\v=====================================================================\v"<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
        cout<<"|             Welcome to the Supershop Management System          |"<<endl;
        cout<<"-------------------------------------------------------------------\v"<<endl;
        cout<<"                   ::Choose a mode to login::                    \v"<<endl;
        cout<<"1. Store Manager"<<endl;
        cout<<"2. Customer"<<endl;
        cout<<"3. Exit"<<endl;
        cin>>n;
        switch(n){
            case 1:
            stock();
                management();
                break;
            case 2:
            if(runtime==false){stock();}
                start_shopping();
                break;
            case 3:
                cout<<"===============================================================================\v"<<endl;
                cout<<"\v    THANKS FOR CHOOSING OUR SERVICE, MADE BY REZUAN, ABIR & SARWAD\v"<<endl<<endl;
                cout<<"               THE MANAGEMENT SYSTEM IS EXITING...\v"<<endl;
                break;
        }
    }

}
void supershop::start_shopping() {
    int id = 0, q=0, pro_id;
    string name, address, contact_num, email, gender, choice = "Yes";
    cout<<"================================================================================================\v"<<endl;
    cout << "-------------------------------- -WELCOME TO OUR SUPERSHOP!!!----------------------------------\v" << endl;
    cout <<"          I am " << (office1.get_cashier(0).getname()) << ", the cashier and I will be here the whole time to assist you!\v" << endl;
    cout << "BUT BEFORE YOU CAN START BROWSING AND START SHOPPING HERE WE NEED TO REGISTER YOUR INFORMATIONS!!!\v\v" << endl;
    cin.ignore();
    fflush(stdin);
    cout<<"Please enter your id:"<<endl<<endl;
    cin>>id;
    cout<<endl;
    cart1.removeall();
    if(!database.find_customers(id)){
        cin.ignore();
        fflush(stdin);
    cout << "Please enter your name:" << endl<<endl;
    getline(cin, name);
    cout<<endl;
    cout << "Please enter your address:" << endl<<endl;
    getline(cin, address);
    cout<<endl;
    cout << "Please enter your contact number:" << endl<<endl;
    getline(cin, contact_num);
    cout<<endl;
    cout << "Please enter your email address:" << endl<<endl;
    getline(cin, email);
    cout<<endl;
    cout << "Please enter your gender:" << endl<<endl;
    getline(cin, gender);
    cout<<endl;
    customer customer1(id, name, address, contact_num, email, gender);
    database.add_customers(customer1);
    gender = (gender == "Male") ? " Sir" : " Madam";
    cout << "Thank you for being with us here today " << customer1.get_name() <<", "<< gender <<"!\v"<< endl;
    cout << "Please let us know how can we be of your service today," << gender << ":\v" << endl<<endl;
    }
    else{
        cout<<endl;
       
        cout<<"=================================================================================================\v"<<endl;
        gender = ((database.customer_getter(id).get_gender()=="Male")?"Sir!":"Madam!");
        cout<<"Welcome Back, "<< database.customer_getter(id).get_name()<<" "<<gender<<"\v"<<endl;
        cout << "Please let us know how can we be of your service today," << gender << ":\v" << endl<<endl;
        cout <<"=================================================================================================\v\v\v"<<endl;
    }
    while (q != 7) {
        cout << "1. Show the whole inventory of products" << endl<<endl;
        cout << "2. Show only the available products" << endl<<endl;
        cout << "3. Start Shopping from the available products" << endl<<endl;
        cout << "4. Request Restock of an unavailable product" << endl<<endl;
        cout << "5. Search a product" << endl<<endl;
        cout << "6. Search a category" << endl<<endl;
        cout << "7. Exit & Process your purchase" << endl<<endl;
        cin >> q;
        switch (q) {
        case 1:
            inventory1.show_all();
            break;
        case 2:
            inventory1.show_avail();
            break;
        case 3:
        {
            inventory1.show_avail();
            int p = 0;
            while (p != 4) {
                cout << "Choose your query" << endl<<endl;
                cout << "1. Add a product to cart" << endl<<endl;
                cout << "2. Remove a product from cart" << endl<<endl;
                cout << "3. Show your cart" << endl<<endl;
                cout << "4. Checkout" << endl<<endl;
                cin >> p;
                switch (p) {
                case 1:
                {
                    int pro_id,quantity;
                    int t;
                    do {
                        cout << "\nWhich product do you want?Please enter it's id and quantity:" << endl<<endl;
                        cout << "ID: " << endl<<endl;
                        cin >> pro_id;
                        cout<<endl;
                        cout << "Quantity: " << endl;
                        cin >> quantity;
                        cout<<endl;
                        cart1.add_to_cart(inventory1,pro_id,quantity,&t);
                        if(t!=NULL){
                            inventory1.products.at(t).remove_stock(quantity);
                            
                        }
                        cout << "Do you want to add more products?Type Yes/yes if you want to." << endl<<endl;
                        cin >> choice;
                        cout<<"\v"<<endl;
                    } while (choice == "Yes" || choice == "yes");
                    
                }
                    break;
                case 2:
                {
                    int pro_id,quantity;
                    int t;
                    do {
                        cout << "\nWhich product do you want to remove from the cart?Please enter it's id and quantity:" << endl;
                        cout << "ID: " << endl<<endl;
                        cin >> pro_id;
                        cout<<endl;
                        cout << "Quantity: " << endl<<endl;
                        cin >> quantity;
                        cout<<endl;
                        cart1.remove_from_cart(inventory1,pro_id,quantity,&t);
                        if(t!=NULL){
                            inventory1.products.at(t).add_stock(quantity);
                        }
                        cout << "Do you want to remove more products?Type Yes/yes if you want to." << endl<<endl;
                        cin >> choice;
                        cout<<"\v"<<endl;
                    } while (choice == "Yes" || choice == "yes");
                    
                }
                    break;
                case 3:
                    cout << "You have " << cart1.total_product() << " products in your cart" << endl;
                    cart1.show_cart();
                    break;
                case 4:
                    system("cls");
                    cout << "You have " << cart1.total_product()<< " products in your cart" << endl;
                    cart1.show_cart();
                    cout << "\vTotal price: " << cart1.grand_total() << " Tk/-\v" << endl;
                    cout <<"\vChecking out.......\v"<<endl;
                    break;
                }
            }
            
        }
            break;
        case 4:
            cout<<"Please enter the id of the product which you want to be restocked:"<<endl;
            cout<<"ID: "<<endl;
            cin>>pro_id;
            cout << "Your request has been processed! Thanks for your input!" << endl;
            break;
            case 5:
            {
                cin.ignore();
                fflush(stdin);
                string s;
                int i;
                cout<<"Enter the wanted name:";
                getline(cin,s);
            search_by_name(inventory1.products,s,&i);
            }
            break;
            case 6:
            category_search(inventory1.products);
            break;
        case 7:
            system("cls");
            cashier1.process_payment(cart1, customer1);
            break;
        }
    }
}
int main(){ 
    supershop Shopno;
    Shopno.modeselect();
    return 0;
} 
