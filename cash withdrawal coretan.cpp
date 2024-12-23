#include<iostream>
#include<windows.h>

// Define function pointers for XFS functions
typedef HRESULT (*WFSStartUp_t)(DWORD, LPWFSVERSION, LPWFSVERSION);
typedef HRESULT (*WFSCleanUp_t)();

class CashDispenser : public ATMDevice{
	public:
		void initialize();
		void reset();
		void getStatus();
		void dispenseCash(int amount);
		void cashWithdrawal(int amount);
		void cashDeposit(int amount);
};

int main(){
	int choice;
	int amount;
	
	do{
		system("cls");
		std::cout << "======Cash Dispenser======";
		std::cout << "1. Setor Tunai\n";
		std::cout << "2. Tarik Tunai\n";
		std::cout << "3. Keluar\n";
		std::cout << "Pilihan: ";
		std::cin >> choice;
		switch(choice){
			case 1:
				int nominal, pilihan;
				std::cout << "Nominal yang akan di setor: ";
				std::cin >> nominal;
				if(nominal <= 0){
					std::cerr << "Nominal tidak valid! Silahkan input kembali! Error: " << GetLastError() << std::endl;
				}else if(nominal < 50000){
					std::cerr << "Nominal bukan kelipatan 50.000. Silahkan masukkan uang kembali. Error: " << GetLastError() <<std::endl;
				}else if(nominal%50000 == 0){
					std::cout << "Uang yang akan di setor sebesar " << nominal << std::endl;
					std::cout << "Transaksi selesai\n";
					std::cout << "Apakah ada transaksi lain?\n";
					std::cout << "1. Iya\n2. Tidak\n";
					std::cout << "Pilihan: ";
					std::cin >> pilihan;
					if(pilihan == 2){
						return 0;
					}else{
						return;
					}
				}else{
					std::cerr << "Nominal bukan kelipatan 50.000. Silahkan masukkan uang kembali. Error: " << GetLastError() <<std::endl;
				}
				break;
			case 2:
				
				break;
			case 3:
				std::cout << "Terimakasih telah menggunakan sistem ini!\n";
				break;
			default:
				std::cerr << "Pilihlah angka 1-3!" << GetLastError() << std::endl;
		}
	}while(choice!= 3)
	
	return 0;
}
