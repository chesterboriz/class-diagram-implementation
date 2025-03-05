#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int MAX_PRODUCTS = 5;
const int MAX_CART = 10;
const int MAX_ORDERS = 5;

struct Product {
    string productID;
    string name;
    double price;
};

struct CartItem {
    Product product;
    int quantity;
};

struct Order {
    int orderID;
    CartItem items[MAX_CART];
    int itemCount;
    double totalAmount;
};

Product products[MAX_PRODUCTS] = {
    {"ABC", "Paper", 20.0},
    {"CDE", "Pencil", 10.0},
    {"FGH", "Notebook", 50.0},
    {"IJK", "Eraser", 5.0},
    {"LMN", "Marker", 15.0}
};

CartItem cart[MAX_CART];
int cartSize = 0;
Order orders[MAX_ORDERS];
int orderCount = 0;

double calculateTotal(CartItem cart[], int size) {
    double total = 0;
    for (int i = 0; i < size; i++) {
        total += cart[i].product.price * cart[i].quantity;
    }
    return total;
}

void clearCart() {
    cartSize = 0;
    cout << "Cart has been cleared successfully!\n";
}

void viewProducts() {
    cout << "-----------------------------------" << endl;
    cout << "| Product ID | Name | Price |" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        cout << "| " << products[i].productID << " | " << products[i].name << "   | " << products[i].price << " |" << endl;
    }
    cout << "-----------------------------------" << endl;
}

void addToCart() {
    string id;
    int quantity;
    bool found = false;

    cout << "Enter Product ID to add (ABC-LMN): ";
    cin >> id;

    for (char &c : id) {
        c = toupper(c);
    }

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].productID == id) {
            found = true;
            cout << "Enter Quantity: ";
            while (!(cin >> quantity) || quantity <= 0) {
                cout << "Invalid quantity! Please enter a positive number: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cart[cartSize].product = products[i];
            cart[cartSize].quantity = quantity;
            cartSize++;
            cout << "Product added to cart successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "Invalid Product ID.\n";
    }
}

void removeFromCart() {
    if (cartSize == 0) {
        cout << "Your cart is empty!\n";
        return;
    }
    string id;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    for (char &c : id) {
        c = toupper(c);
    }

    bool found = false;
    for (int i = 0; i < cartSize; i++) {
        if (cart[i].product.productID == id) {
            found = true;
            for (int j = i; j < cartSize - 1; j++) {
                cart[j] = cart[j + 1];
            }
            cartSize--;
            cout << "Product removed from cart successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "Product not found in cart.\n";
    }
}

void viewCart() {
    if (cartSize == 0) {
        cout << "Your cart is empty!\n";
        return;
    }
    cout << "------------------------------------------------" << endl;
    cout << "| Product ID | Name | Price | Quantity |" << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < cartSize; i++) {
        cout << "| " << cart[i].product.productID << " | " << cart[i].product.name << "   | " << cart[i].product.price << " |    " << cart[i].quantity << "    |" << endl;
    }
    cout << "------------------------------------------------" << endl;
    cout << "Total Amount: " << calculateTotal(cart, cartSize) << endl;
}

void checkout() {
    if (cartSize == 0) {
        cout << "Your cart is empty! Cannot proceed to checkout.\n";
        return;
    }
    double total = calculateTotal(cart, cartSize);
    if (orderCount < MAX_ORDERS) {
        orders[orderCount].orderID = orderCount + 1;
        orders[orderCount].itemCount = cartSize;
        orders[orderCount].totalAmount = total;
        for (int i = 0; i < cartSize; i++) {
            orders[orderCount].items[i] = cart[i];
        }
        orderCount++;
        clearCart();
        cout << "Checkout successful! Total Amount: " << total << endl;
    } else {
        cout << "Order limit reached!" << endl;
    }
}

void viewOrders() {
    for (int i = 0; i < orderCount; i++) {
        cout << "------------------------------------------------" << endl;
        cout << "Order ID: " << orders[i].orderID << "\nTotal Amount: " << orders[i].totalAmount << "\nOrder Details:" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "| Product ID | Name | Price | Quantity |" << endl;
        for (int j = 0; j < orders[i].itemCount; j++) {
            cout << "| " << orders[i].items[j].product.productID << " | " << orders[i].items[j].product.name << "   | " << orders[i].items[j].product.price << " |    " << orders[i].items[j].quantity << "    |" << endl;
        }
        cout << "------------------------------------------------" << endl;
        cout << "Total Amount: " << orders[i].totalAmount << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. View Products\n2. Add to Cart\n3. View Cart\n4. Remove from Cart\n5. Checkout\n6. View Orders\n7. Clear Cart\n8. Exit\nEnter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 8) {
            cout << "Invalid input! Please enter a number between 1 and 8: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: addToCart(); break;
            case 3: viewCart(); break;
            case 4: removeFromCart(); break;
            case 5: checkout(); break;
            case 6: viewOrders(); break;
            case 7: clearCart(); break;
            case 8: cout << "Exiting...\n"; break;
        }
    } while (choice != 8);

    return 0;
}
