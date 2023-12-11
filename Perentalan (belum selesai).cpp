#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int MAX_MOTORS = 100;
const int MAX_AVAILABLE_MOTORS = 100;
const int MAX_QUEUED_CUSTOMERS = 100;

// proses motor dengan stack
struct motor {
    string merk;
    string platNomor;
    double hargaSewa;
    bool tersedia;
};

struct MotorStack {
    stack<motor> motors;

    void pushMotor(const motor& m) {
        motors.push(m);
    }

    void displayMotors() {
        if (motors.empty()) {
            cout << "Stack motor kosong." << endl;
            return;
        }

        cout << "Daftar Motor:" << endl;
        stack<motor> temp = motors;
        while (!temp.empty()) {
            motor currentMotor = temp.top();
            cout << "Merk: " << currentMotor.merk << ", Plat Nomor: " << currentMotor.platNomor
                 << ", Harga Sewa: " << currentMotor.hargaSewa << ", Tersedia: " << (currentMotor.tersedia ? "Ya" : "Tidak") << endl;
            temp.pop();
        }
    }
    motor* searchMotorByPlatNomor(const string& platNomorToSearch) {
        stack<motor> temp;
        motor* foundMotor = NULL;

        while (!motors.empty()) {
            motor currentMotor = motors.top();
            motors.pop();

            if (currentMotor.platNomor == platNomorToSearch) {
                foundMotor = &currentMotor; // Motor ditemukan, set pointer ke motor yang ditemukan
                break;
            }

            temp.push(currentMotor);
        }

        // Kembalikan motor-motor yang tidak dicari ke dalam stack
        while (!temp.empty()) {
            motors.push(temp.top());
            temp.pop();
        }

        return foundMotor;
    }
    
};
void inputMotor(MotorStack& motorStack) {
    motor newMotor;
    cout << "Merk: ";
    cin >> newMotor.merk;
    cout << "Plat Nomor: ";
    cin >> newMotor.platNomor;
    cout << "Harga Sewa: ";
    cin >> newMotor.hargaSewa;
    cout << "Tersedia (1 = Ya, 0 = Tidak): ";
    cin >> newMotor.tersedia;

    // Menambahkan motor ke dalam stack motor
    motorStack.pushMotor(newMotor);
}

// struct date untuk menyimpan tanggal
struct Date {
    int day;
    int month;
    int year;

    Date() {}
    
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
};

// proses input data customer dengan queue
struct customer {
    string nama;
    string alamat;
    string no_telp;
    string nik;
};

struct QueuedCustomerQueue {
    customer customers[MAX_QUEUED_CUSTOMERS];
    int front, rear, itemCount;

    QueuedCustomerQueue() {
        front = 1;
        rear = -1;
        itemCount = 1;
    }

    bool isEmpty() {
        return itemCount == 0;
    }

    bool isFull() {
        return itemCount == MAX_QUEUED_CUSTOMERS;
    }

    void enqueue(const customer& newCustomer) {
        if (!isFull()) {
            if (rear == MAX_QUEUED_CUSTOMERS - 1) {
                rear = -1;
            }
            customers[++rear] = newCustomer;
            itemCount++;
        } else {
            cout << "Antrian penuh, tidak dapat menambahkan customer." << endl;
        }
    }

    void inputCustomer() {
        customer newCustomer;
        cout << "Masukkan Nama: ";
        cin >> newCustomer.nama;
        cout << "Masukkan Alamat: ";
        cin >> newCustomer.alamat;
        cout << "Masukkan Nomor Telepon: ";
        cin >> newCustomer.no_telp;
        cout << "Masukkan NIK: ";
        cin >> newCustomer.nik;

        enqueue(newCustomer); // Memasukkan customer ke dalam antrian
    }
};


Date inputDate() {
    int day, month, year;
    bool isValidDate = false;

    do {
        cout << "Masukkan tanggal (DD MM YYYY): ";
        cin >> day >> month >> year;

        // Validasi tanggal
        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900) {
            isValidDate = true;
        } else {
            cout << "Tanggal tidak valid. Harap masukkan tanggal dengan benar." << endl;
        }
    } while (!isValidDate);

    return Date(day, month, year);
}

// proses sewa motor <belum linked list>
struct sewa {
    string nonota;
    motor motorSewa;
     Date tgl_sewa;          // Tanggal sewa
    Date tgl_kembali;       // Tanggal kembali
    Date tgl_harusKembali;  // Tanggal yang harus dikembalikan
    double denda;
    double total;

    // Constructor untuk struktur sewa
    
};

void sewaMotor(QueuedCustomerQueue& queuedCustomers, MotorStack& motorStack) {
     if (queuedCustomers.isEmpty()) {
        cout << "Antrian customer kosong." << endl;
        return;
    }

    if (motorStack.motors.empty()) {
        cout << "Tidak ada motor tersedia untuk disewa." << endl;
        return;
    }

    cout << "Daftar Antrian Customer:" << endl;
    for (int i = queuedCustomers.front; i <= queuedCustomers.rear; ++i) {
        cout << i << ". " << queuedCustomers.customers[i].nama << endl;
    }

    int customerIndex;
    cout << "Pilih customer (masukkan nomor): ";
    cin >> customerIndex;

    if (customerIndex < queuedCustomers.front || customerIndex > queuedCustomers.rear) {
        cout << "Nomor customer tidak valid." << endl;
        return;
    }

    customer currentCustomer = queuedCustomers.customers[customerIndex];

    motorStack.displayMotors();

    string platNomorToSearch;
    cout << "Masukkan plat nomor motor yang ingin disewa: ";
    cin >> platNomorToSearch;

    motor* foundMotor = motorStack.searchMotorByPlatNomor(platNomorToSearch);

    if (foundMotor ==  NULL) {
        cout << "Motor dengan plat nomor tersebut tidak tersedia." << endl;
        return;
    }

    if (!foundMotor->tersedia) {
        cout << "Motor tidak tersedia untuk disewa saat ini." << endl;
        return;
    }

  cout << "Merk: " << foundMotor->merk << ", Plat Nomor: " << foundMotor->platNomor
     << ", Harga Sewa: " << foundMotor->hargaSewa << ", Tersedia: " << (foundMotor->tersedia ? "Ya" : "Tidak") << endl;

    // Memasukkan data sewa dari input pengguna
    sewa newSewa;
    cout << "Masukkan nomor nota: ";
    cin >> newSewa.nonota;
    
     cout << "Masukkan tanggal awal sewa" << endl;
    newSewa.tgl_sewa = inputDate();

    cout << "Masukkan tanggal harus kembali sewa" << endl;
    newSewa.tgl_harusKembali = inputDate();

   // cout << "Masukkan tanggal kembali sewa" << endl;
    //newSewa.tgl_kembali = inputDate();

    newSewa.denda = 0; // Awalnya denda 0, akan dihitung jika keterlambatan pengembalian motor
    newSewa.total = 0; // Awalnya total biaya 0, akan dihitung saat pembayaran

    // Mengubah status motor menjadi tidak tersedia
     foundMotor->tersedia = false;

    // Mengeluarkan motor dari stack karena sudah disewa
    motorStack.motors.pop();

     // Menampilkan informasi sewa
    cout << "Motor berhasil disewa oleh " << currentCustomer.nama << " pada tanggal "
         << newSewa.tgl_sewa.day << "/" << newSewa.tgl_sewa.month << "/" << newSewa.tgl_sewa.year
         << " hingga tanggal "
         << newSewa.tgl_harusKembali.day << "/" << newSewa.tgl_harusKembali.month << "/" << newSewa.tgl_harusKembali.year
         << "." << endl;

   
}



int tampilkanMenu(QueuedCustomerQueue& queuedCustomers, MotorStack& motorStack) {
    int pilihan;
    cout << "\n=== MENU ===" << endl;
    cout << "1. Input Data Customer" << endl;
    cout << "2. Input Data Motor" << endl;
    cout << "3. Tampilkan List Motor" << endl;
    cout << "4. Sewa Motor" << endl;
    cout << "5. Pembayaran" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu (1-6): ";
    cin >> pilihan;
    system("cls");

    switch (pilihan) {
        case 1:
            queuedCustomers.inputCustomer(); // Panggil fungsi inputCustomer untuk memasukkan data customer
            break;
        case 2: {
            inputMotor(motorStack); // Panggil fungsi inputMotor untuk memasukkan data motor
            break;

        }
        break;
        case 3:
            motorStack.displayMotors();
            break;
        case 4:
            sewaMotor(queuedCustomers, motorStack);
            break;
    }

    return pilihan;
}

int main() {
    QueuedCustomerQueue queuedCustomers;
    MotorStack motorStack;
    int pilihan;

    do {
        pilihan = tampilkanMenu(queuedCustomers, motorStack);
    } while (pilihan != 6); // Perubahan pilihan keluar (exit) saat input 6 dipilih

    return 0;
}
