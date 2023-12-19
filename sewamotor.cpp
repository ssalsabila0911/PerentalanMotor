#include <iostream>
#include <cstdlib>

using namespace std;

const int MAX_QUEUED_CUSTOMERS = 100;
const int MAX_SEWA_HISTORY = 100;


struct Date {
    int day;
    int month;
    int year;

    Date() {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
};
Date inputDate() {
    Date date;
    cout << "Masukkan tanggal (tanggal bulan tahun): ";
    cin >> date.day >> date.month >> date.year;
    return date;
}

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
        front = 0;
        rear = -1;
        itemCount = 0;
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
    	char tambah;
    	
        do{
        
        customer newCustomer;
        cout << "Masukkan Nama: ";
        cin >> newCustomer.nama;
        cout << "Masukkan Alamat: ";
        cin >> newCustomer.alamat;
        cout << "Masukkan Nomor Telepon: ";
        cin >> newCustomer.no_telp;
        cout << "Masukkan NIK: ";
        cin >> newCustomer.nik;

        enqueue(newCustomer);
        cout << "Data customer berhasil ditambahkan." << endl;
        cout<<"Ingin menambahkan customer lagi? (y/n): ";
        cin>>tambah;
		}while (tambah=='y'||tambah=='Y');
    }
};

struct MotorNode {
    string merk;
    string platNomor;
    double hargaSewa;
    bool tersedia;
    MotorNode* next;

    MotorNode(const string& m, const string& plat, double harga, bool avail)
        : merk(m), platNomor(plat), hargaSewa(harga), tersedia(avail), next(nullptr) {}
};

class MotorLinkedList {
private:
    MotorNode* head;
    int indeksMotorStatisTerakhir;

public:
    MotorLinkedList() : head(nullptr), indeksMotorStatisTerakhir(-1) {}

    bool isEmpty() const {
        return head == nullptr;
    }

    void pushMotor(const string& merk, const string& platNomor, double hargaSewa, bool tersedia) {
        MotorNode* newMotor = new MotorNode(merk, platNomor, hargaSewa, tersedia);

        if (indeksMotorStatisTerakhir == -1) {
            newMotor->next = head;
            head = newMotor;
        } else {
            MotorNode* current = head;
            for (int i = 0; i < indeksMotorStatisTerakhir; ++i) {
                current = current->next;
            }
            newMotor->next = current->next;
            current->next = newMotor;
        }

        indeksMotorStatisTerakhir++;
    }

    void displayMotors() {
        if (head == nullptr || indeksMotorStatisTerakhir == -1) {
            cout << "Tidak ada motor tersedia." << endl;
            return;
        }

        MotorNode* current = head;
        cout << "Daftar Motor :" << endl;
        for (int i = 0; i <= indeksMotorStatisTerakhir; ++i) {
            cout << "Merk: " << current->merk << ", Plat Nomor: " << current->platNomor
                << ", Harga Sewa: " << current->hargaSewa << ", Tersedia: " << (current->tersedia ? "Ya" : "Tidak") << endl;
            current = current->next;
        }
    }

    MotorNode* searchMotorByPlatNomor(const string& platNomorToSearch) {
        MotorNode* current = head;
        while (current != nullptr) {
            if (current->platNomor == platNomorToSearch) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool removeMotorByPlatNomor(const string& platNomorToRemove) {
    MotorNode* current = head;
    while (current != nullptr) {
        if (current->platNomor == platNomorToRemove) {
            current->tersedia = false;  // Ganti status tersedia menjadi false
            return true;
        }
        current = current->next;
    }
    return false;
}


    ~MotorLinkedList() {
        MotorNode* current = head;
        while (current != nullptr) {
            MotorNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};


struct SewaMotor {
    string nonota;
    MotorNode* motorSewa;
    Date tgl_sewa;
    Date tgl_kembali;
    Date tgl_harusKembali;
    int lamaSewa;
    double biayaSewa;
    double denda;
    SewaMotor() : motorSewa(nullptr){
	}
};
struct SewaMotorStack {
	
private:
    SewaMotor sewaHistory[MAX_SEWA_HISTORY];
    int top;
    


public:
    SewaMotorStack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_SEWA_HISTORY - 1;
    }
    

    void push(const SewaMotor& sewaData) {
        if (!isFull()) {
            sewaHistory[++top] = sewaData;
            
        } else {
            cout << "Stack penyewaan penuh, tidak dapat menambahkan data penyewaan." << endl;
        }
    }
     void sortSewaByDate() {
        for (int i = 0; i <= top; ++i) {
            for (int j = 0; j <= top - i - 1; ++j) {
                if (sewaHistory[j].tgl_sewa.year > sewaHistory[j + 1].tgl_sewa.year ||
                    (sewaHistory[j].tgl_sewa.year == sewaHistory[j + 1].tgl_sewa.year &&
                     sewaHistory[j].tgl_sewa.month > sewaHistory[j + 1].tgl_sewa.month) ||
                    (sewaHistory[j].tgl_sewa.year == sewaHistory[j + 1].tgl_sewa.year &&
                     sewaHistory[j].tgl_sewa.month == sewaHistory[j + 1].tgl_sewa.month &&
                     sewaHistory[j].tgl_sewa.day > sewaHistory[j + 1].tgl_sewa.day)) {
                    SewaMotor temp = sewaHistory[j];
                    sewaHistory[j] = sewaHistory[j + 1];
                    sewaHistory[j + 1] = temp;
                }
            }
        }
    }

    
    // Menampilkan data - data sewa
   void displaySewaStack(const QueuedCustomerQueue& queuedCustomers) const {
    for (int i = top; i >= 0; --i) {
        cout << "Data Penyewaan:" << endl;
        const SewaMotor& sewa = sewaHistory[i];
        int customerIndex = (queuedCustomers.front + queuedCustomers.itemCount - 1 - i) % MAX_QUEUED_CUSTOMERS;
        const customer& currentCustomer = queuedCustomers.customers[customerIndex];
        cout << "Nama Penyewa: " << currentCustomer.nama << endl;
        cout << "Motor sewa: " << sewa.motorSewa->merk << " - " << sewa.motorSewa->platNomor << endl;
        cout << "Tanggal Sewa: " << sewa.tgl_sewa.day << "/" << sewa.tgl_sewa.month << "/" << sewa.tgl_sewa.year << endl;
        cout << "Tanggal Kembali: " << sewa.tgl_kembali.day << "/" << sewa.tgl_kembali.month << "/" << sewa.tgl_kembali.year << endl;

    }
} void displaySortedSewa() const {
        SewaMotorStack tempStack = *this; // Buat salinan stack untuk sorting tanpa merusak data asli
        tempStack.sortSewaByDate(); // Urutkan data penyewaan

        for (int i = tempStack.top; i >= 0; --i) {
            // Tampilkan data yang telah diurutkan
            // ... (tampilkan sesuai kebutuhan, mungkin seperti yang telah kamu lakukan sebelumnya)
        }
    }
};;


void sewaMotor(QueuedCustomerQueue& queuedCustomers, MotorLinkedList& motorList, SewaMotorStack& sewaStack);
void tampilInformasi(const customer& penyewa, const SewaMotor& sewa);
double hitungDenda(const SewaMotor& sewa);
double hitungTotal(const SewaMotor& sewa);


void sewaMotor(QueuedCustomerQueue& queuedCustomers, MotorLinkedList& motorList, SewaMotorStack& sewaStack) {
	
    if (queuedCustomers.isEmpty()) {
        cout << "Antrian customer kosong." << endl;
        return;
    }

    if (motorList.isEmpty()) {
        cout << "Tidak ada motor tersedia untuk disewa." << endl;
        return;
    }

    customer currentCustomer = queuedCustomers.customers[queuedCustomers.front]; // Ambil customer dari depan antrian
    
    cout << queuedCustomers.front  + 1 <<" Nama Penyewa: " << currentCustomer.nama  << endl;

    motorList.displayMotors();

    string platNomorToSearch;
    cout << "Masukkan plat nomor motor yang ingin disewa: ";
    cin >> platNomorToSearch;

    MotorNode* foundMotor = motorList.searchMotorByPlatNomor(platNomorToSearch);

      if (foundMotor == nullptr || !foundMotor->tersedia) {
        cout << "Motor dengan plat nomor tersebut tidak tersedia." << endl;
        return;
    }

    cout << "Merk: " << foundMotor->merk << ", Plat Nomor: " << foundMotor->platNomor
         << ", Harga Sewa: " << foundMotor->hargaSewa << ", Tersedia: " << (foundMotor->tersedia ? "Ya" : "Tidak") << endl;

    SewaMotor newSewa;
  
	cout << "Masukkan tanggal sewa" << endl;
    newSewa.tgl_sewa = inputDate();

    
    // Hitung tanggal kembali berdasarkan lama sewa
    int lamaSewa;
    cout << "Masukkan lama sewa (dalam hari): ";
    cin >> lamaSewa;

    newSewa.tgl_kembali.day = newSewa.tgl_sewa.day + lamaSewa;
    newSewa.tgl_kembali.month = newSewa.tgl_sewa.month;
    newSewa.tgl_kembali.year = newSewa.tgl_sewa.year;

    // Handle jika tanggal kembali melebihi 30 hari dalam satu bulan atau beralih ke tahun berikutnya
    if (newSewa.tgl_kembali.day > 30) {
        newSewa.tgl_kembali.day -= 30;
        newSewa.tgl_kembali.month++;

        if (newSewa.tgl_kembali.month > 12) {
            newSewa.tgl_kembali.month = 1;
            newSewa.tgl_kembali.year++;
        }
    }
    newSewa.motorSewa = foundMotor;

    foundMotor->tersedia = false;
    motorList.removeMotorByPlatNomor(platNomorToSearch);

    queuedCustomers.front = (queuedCustomers.front + 1) % MAX_QUEUED_CUSTOMERS;
    queuedCustomers.itemCount--;

    
     newSewa.lamaSewa = lamaSewa;
    newSewa.biayaSewa = foundMotor->hargaSewa;  // biaya sewa per hari, dapat disesuaikan

      
tampilInformasi(currentCustomer, newSewa);
sewaStack.push(newSewa);



}	


																		    	
void tampilInformasi(const customer& penyewa, const SewaMotor& sewa) {			
    cout << "\n\t\t||-----------------------Nota Sewa------------------------------||";
    cout << "\n\t\t||==============================================================||";
    cout << "\n\t\t||Nama Penyewa				: " << penyewa.nama << "			||";
    cout << "\n\t\t||Lama Sewa				: " << sewa.lamaSewa    << " Hari		||";
    cout << "\n\t\t||Tanggal Sewa				: " << sewa.tgl_sewa.day << "/" << sewa.tgl_sewa.month << "/" << sewa.tgl_sewa.year << "		||";
    cout << "\n\t\t||Tanggal Kembali			: " << sewa.tgl_kembali.day << "/" << sewa.tgl_kembali.month << "/" << sewa.tgl_kembali.year << "		||";
    cout << "\n\t\t||Motor Sewa				: " << sewa.motorSewa->merk << " - " << sewa.motorSewa->platNomor 								 << "	||";
    cout << "\n\t\t||Harga Sewa Per Hari			: " << sewa.motorSewa->hargaSewa 													     << "        	||";
    cout << "\n\t\t||Total Biaya				: " << hitungTotal(sewa) << "        	||";
    cout << "\n\t\t||==============================================================||";
}


void tambahDataMotor(MotorLinkedList& motorList) {
    motorList.pushMotor("Suzuki", "B9876", 150000, true);
    motorList.pushMotor("Kawasaki", "B5432", 130000, true);
    motorList.pushMotor("Honda", "B1234", 120000, true);
    motorList.pushMotor("Yamaha", "B3456", 140000, true);
    
}

double hitungTotal(const SewaMotor& sewa) {
    // Menghitung total biaya berdasarkan lama sewa dan biaya sewa per hari
    double totalBiaya = sewa.lamaSewa * sewa.biayaSewa;

    return totalBiaya;
}

double hitungDenda(const SewaMotor& sewa) {
    // Hitung selisih dalam hari antara tanggal pengembalian aktual dan tanggal jatuh tempo
    int selisihHari = (sewa.tgl_kembali.year - sewa.tgl_harusKembali.year) * 365 +
                      (sewa.tgl_kembali.month - sewa.tgl_harusKembali.month) * 30 +
                      (sewa.tgl_kembali.day - sewa.tgl_harusKembali.day);

    // Biaya keterlambatan per hari
    const double dendaPerHari = 80000.0;

    // Hitung total biaya keterlambatan
    double totalDenda = max(selisihHari, 0) * dendaPerHari;

    return totalDenda;
}


void kembalikanMotor(QueuedCustomerQueue& queuedCustomers, MotorLinkedList& motorList, SewaMotorStack& sewaStack) {
    cout << "Masukkan plat nomor motor yang akan dikembalikan: ";
    string platNomorMotor;
    cin >> platNomorMotor;

    MotorNode* returnedMotor = motorList.searchMotorByPlatNomor(platNomorMotor);

    if (returnedMotor == nullptr) {
        cout << "Motor dengan plat nomor tersebut tidak ditemukan." << endl;
        return;
    }

    cout << "Merk: " << returnedMotor->merk << ", Plat Nomor: " << returnedMotor->platNomor
         << ", Harga Sewa: " << returnedMotor->hargaSewa << ", Tersedia: " << (returnedMotor->tersedia ? "Ya" : "Tidak") << endl;

   Date tanggalKembali;
    cout << "Masukkan tanggal kembali seharusnya \n ";
    tanggalKembali = inputDate();
	

    SewaMotor* sewaMotor = new SewaMotor(); // Untuk menyimpan data penyewaan yang sedang diproses
    sewaMotor->motorSewa = returnedMotor;
    sewaMotor->tgl_harusKembali = sewaMotor->tgl_kembali = tanggalKembali;

   cout << "Masukkan tanggal kembali keterlambatan" << endl;
    sewaMotor->tgl_kembali = inputDate();


    // Hitung biaya keterlambatan
    sewaMotor->denda = hitungDenda(*sewaMotor);

    // Tampilkan informasi termasuk biaya keterlambatan
    cout << "Denda: " << sewaMotor->denda << endl;
    returnedMotor->tersedia = true;

    // Simpan data penyewaan ke dalam stack
}
void bubbleSortSewa(SewaMotor sewaHistory[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // Bandingkan tanggal sewa untuk swap jika diperlukan
            if (sewaHistory[j].tgl_sewa.year > sewaHistory[j + 1].tgl_sewa.year ||
                (sewaHistory[j].tgl_sewa.year == sewaHistory[j + 1].tgl_sewa.year &&
                 sewaHistory[j].tgl_sewa.month > sewaHistory[j + 1].tgl_sewa.month) ||
                (sewaHistory[j].tgl_sewa.year == sewaHistory[j + 1].tgl_sewa.year &&
                 sewaHistory[j].tgl_sewa.month == sewaHistory[j + 1].tgl_sewa.month &&
                 sewaHistory[j].tgl_sewa.day > sewaHistory[j + 1].tgl_sewa.day)) {
                // Lakukan swap jika data perlu ditukar
                SewaMotor temp = sewaHistory[j];
                sewaHistory[j] = sewaHistory[j + 1];
                sewaHistory[j + 1] = temp;
            }
        }
    }
}




int tampilkanMenu(QueuedCustomerQueue& queuedCustomers, MotorLinkedList& motorList, SewaMotorStack& sewaStack) {
    int pilihan;
    cout << "\n=== MENU ===" << endl;
    cout << "1. Input Data Customer" << endl;
    cout << "2. Tampilkan List Motor" << endl;
    cout << "3. Sewa Motor" << endl;
    cout << "4. kembalikan motor" << endl;
    cout << "5. Data sewa" <<endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu (1-6): ";
    cin >> pilihan;
	system("cls");
    switch (pilihan) {
        case 1:
            queuedCustomers.inputCustomer();
            break;
        case 2:
            motorList.displayMotors();
            break;
        case 3:
            sewaMotor(queuedCustomers, motorList, sewaStack );
            break;
        case 4 :
        	sewaStack.displaySewaStack(queuedCustomers);
        	kembalikanMotor(queuedCustomers, motorList, sewaStack);
        	break;
        case 5 :
        	sewaStack.displaySewaStack(queuedCustomers);
            break;
        // Kasus 5-6 dan logika lainnya...
    }
	
    return pilihan;
}

int main() {
    QueuedCustomerQueue queuedCustomers;
    MotorLinkedList motorList;
    tambahDataMotor(motorList);
    SewaMotorStack sewaStack;
    int pilihan;								
	cout << "\n\t\t||==============================================================================||"; 											
	cout << "\n\t\t||			Selamat Datang Di Rental Tujuh				||";
    cout << "\n\t\t||==============================================================================||"; 
    cout<< endl;
	   do {
        pilihan = tampilkanMenu(queuedCustomers, motorList, sewaStack);
    } while (pilihan != 6);
        cout << "Program selesai. Terima kasih!" << endl;


    return 0;
}
