#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct userRegister // informações de cada um dos usuários
{
    string userName, cpf;
    long int userId;
    float dailyPrice;
    short int days;
    double totalPrice;
};

void contUser(userRegister vet[], int&tam){
	int aux = 0;
	for (int i = 0; i < tam; i++){
		if (vet[i].userId != -1){
			aux++;
		}
	}
	tam = aux;
}

userRegister* addRegister(userRegister vet[], int&tam){
	userRegister *newVector = new userRegister[tam+1];
	copy(vet,&vet[tam],newVector);
	tam++;
	delete [] vet;
	return newVector;
}

userRegister* allocationRegister(userRegister vet[], int&tam, int menuFunction){
	contUser(vet,tam);
	userRegister *newVector = new userRegister[tam];
	copy(vet,&vet[tam],newVector);
	delete [] vet;
	return newVector;
}

void readRegister(userRegister vet[],int&tam,bool&archive, int menuFunction){
	char LIXO;
    ifstream read ("register.csv");
    if (not(read)) { // caso não encontre um arquivo para ler, retornará para a main
        archive = false;
    } else { // caso encontre, preencherá o vetor de registro
		archive = true;
        for (int i = 0; i < tam; i++) {
			if (not(read)) { // preenchimento de um espaço do vetor que esteja vazio
				vet[i].userId = -1;
				vet[i].cpf = -1;
				vet[i].userName = "-1";
				vet[i].dailyPrice = -1;
				vet[i].days = -1;
				vet[i].totalPrice = -1;
			} else { //preenchimento de vetor de registro
				vet[i].userId = 1000 + i;
				getline(read, vet[i].userName,',');
				getline(read, vet[i].cpf,',');
				/*read >> vet[i].cpf;
				read >> LIXO;*/
				read >> vet[i].dailyPrice;
				read >> LIXO;
				read >> vet[i].days;
				read >> LIXO;
				read >> vet[i].totalPrice;
				read.ignore();
			}
        }
    }
}

void printRegister(userRegister vet[], int tam){ //Função para mostrar os clientes.
	string compare = "-1";
    cout << "ID\t\tNome\t\t\tCPF\t\t\tDiaria\t\tDias\t\tTotal\n";
    for(int i = 0; i < tam; i++) {
		if ((vet[i].userName[0] == compare[0]) and (vet[i].userName[1] == compare[1])){
			
		} else {
			cout << vet[i].userId << "\t\t" << vet[i].userName << "\t\t" << vet[i].cpf << "\t\tR$" << vet[i].dailyPrice << "\t\t" << vet[i].days << "\t\tR$" << vet[i].totalPrice << endl;
		}
    }
    cout << endl;
}

void recordRegister(userRegister vet[], int tam){ //função para gravar o vetor no arquivo.
	ofstream record ("register.csv");
	for(int i = 0; i < tam; i++) {
		record << vet[i].userName << ",";
		record << vet[i].cpf << ",";
		record << vet[i].dailyPrice << ",";
		record << vet[i].days << ",";
		record << vet[i].totalPrice;
		if (i < (tam - 1)){
			record << endl;
		}
	}
}

void mainMenu(int&menuFunction){ //Menu principal com o comando de menu.
	cout << "MENU PRINCIPAL\n";
	cout << "Por favor, digite o numero referente a funcao que gostaria de usar:"<<endl;
    cout << "1. Exibir usuarios cadastrados."<<endl;
    cout << "2. Buscar usuario."<<endl;
    cout << "3. Cadastrar novo usuario"<<endl;
    cout << "4. Deletar usuario existente"<<endl;
    cout << "5. Ordenar usuarios"<<endl;
    cout << "0. Sair do programa."<<endl;
    cout << "\nOpcao desejada--> ";
    cin >> menuFunction;
    cout << endl;
}

void findMenu(int&searchFunction, int&menuFunction){ //Menu mostrado após encontrar um usuário.
	int findFunction = 3;
	while ((findFunction < 0) or (findFunction > 2)){
		cout << "Busca concluida, digite o numero referente a funcao que gostaria de usar:"<<endl;
		cout << "1. Realizar uma nova busca."<<endl;
		cout << "2. Voltar ao menu principal."<<endl;
		cout << "0. Sair do programa."<<endl;
		cout << "\nOpcao desejada--> ";
		cin >> findFunction;
//		cout << endl;
		switch (findFunction){
			case 1:
				cout << "\nRetornando ao menu de busca...\n";
			break;
			
			case 2:
				cout << "\nRetornando ao menu principal...\n";
				searchFunction = 4; // retorna ao menu principal
			break;
			
			case 0:
				cout << "\nEncerrando sistema...";
				searchFunction = 4;
				menuFunction = 0; //encerra o programa;
			break;
			
			default:
				cout << "Digite uma funcao valida.\n\n";
			break;
		}
	}
}

void searchEmpty(userRegister vet[], int&pos,const int tam){
	string seek = "-1";
	int control = 0;
	for (int i = 0; i < tam; i++){
		for (int j = 0; j < 2; j++){
			if (vet[i].userName[j] == seek[j]){
				control++;
			}
		}
		if (control == 2){
			pos = i;
			i = tam;
		}
		control = 0;
	}
}

void searchMenu(int&searchFunction){ //Menu de procura com o comando de busca.
	cout << "MENU DE BUSCA\n";
	cout << "Por favor, digite o numero referente ao tipo de busca que gostaria de usar:\n";
    cout << "1. Buscar por ID.\n";
    cout << "2. Buscar por nome.\n";
	cout << "3. Buscar por CPF\n";
	cout << "4. Voltar ao menu principal.\n";
	cout << "0. Sair do programa.\n";
	cout << "\nOpcao desejada--> ";
    cin >> searchFunction;
    cout << endl;
}

void searchID(userRegister vet[], int&pos, int seek, int tam){ //Função para procurar por ID.
	pos = -1;
	for (int i = 0; i < tam; i++){
		if (vet[i].userId == seek){
			pos = i;
			i = tam;
		}
	}
}

void searchName(userRegister vet[], int&find,const int tam){ //Função para procurar por Nome.
	string seek;
	cout << "Digite o Nome que deseja buscar --> ";
	cin.ignore();
	getline(cin,seek);
	int sizeName, control = 0;
	sizeName = seek.size();
	for (int i = 0; i < tam; i++){
		for (int j = 0; j < sizeName; j++){
			if (vet[i].userName[j] == seek[j]){
				control++;
			}
		}
		if (control == sizeName){
			find++;
			cout << endl << find << ". Usuario: " << vet[i].userName;
		}
		control = 0;
	}
	cout << endl; //visual
}

void searchCPF(userRegister vet[], int&find,const int tam){ //Função para procurar por Nome.
	string seek;
	cout << "Digite o CPF que deseja buscar --> ";
	cin >> seek;
	int sizeCPF, control = 0;
	sizeCPF = seek.size();
	if (sizeCPF == 11){
		for (int i = 0; i < tam; i++){
			for (int j = 0; j < sizeCPF; j++){
				if (vet[i].cpf[j] == seek[j]){
					control++;
				}
			}
			if (control == sizeCPF){
				find++;
				cout << endl << "1. Usuario: " << vet[i].userName;
			}
			control = 0;
		}
	}
	cout << endl; //visual
}

void search(userRegister vet[], int&searchFunction, int&menuFunction, const int tam){ //Função de busca principal.
	int find = 0, pos = -1, seekSearch = 0;
	switch (searchFunction){
		case 1:
			cout << "Digite o ID que deseja buscar --> ";
			cin >> seekSearch;
			searchID(vet,pos,seekSearch,tam);
			if (pos == -1){
				cout << endl; //visual
				cout << "ID invalido. Retornando ao menu de busca...\n";
			} else {
				cout << endl; //visual
				cout << "1. Usuario: " << vet[pos].userName << endl;
				cout << endl; //visual
				findMenu(searchFunction, menuFunction);
			}
			cout << endl; //visual
		break;
           
		case 2:
			searchName(vet, find,tam);
			if (find == 0){
				cout << "Nome invalido. Retornando ao menu de busca...\n";
			} else {
				cout << endl; //visual
				findMenu(searchFunction, menuFunction);
			}
			cout << endl; //visual
		break;
			
		case 3:
			searchCPF(vet, find, tam);
			if (find == 0){
				cout << "CPF invalido. Retornando ao menu de busca...\n";
			} else {
				cout << endl; //visual
				findMenu(searchFunction, menuFunction);
			}
			cout << endl; //visual
		break;
			
		case 4:
				cout << "Retornando ao menu principal...\n\n";
		break;
				
		case 0:
			cout << "Encerrando sistema...";
			searchFunction = 4;
			menuFunction = 0;
		break;
			
		default:
			cout << "Digite uma funcao valida.\n\n";
			searchFunction = 0;
		break;
	}
}

void deleteMenu(userRegister vet[],int tam){
	int positionDelete = -1, idDelete = 0, deleteFunction = 0;
	cout << "MENU DE DELECAO\n";
	cout << "Por favor, digite o ID do usuario a ser deletado: "<<endl;
	cin >> idDelete;
	searchID(vet, positionDelete, idDelete, tam);
	while (positionDelete == -1){
		cout << "ID inexistente. Digite um ID valido: ";
		cin >> idDelete;
		searchID(vet, positionDelete, idDelete, tam);
	}
	cout << endl << "O Id digitado pertence ao usuario: " << vet[positionDelete].userName;
	cout << ". Tem certeza que deseja deletar este usuario?\n1. Sim.\t\t";
	cout << "2.Nao.\nEscolha uma opcao: ";
	cin >> deleteFunction;
	switch (deleteFunction){
		case 1:
			vet[positionDelete].userName = "-1";
			vet[positionDelete].cpf = "-1";
			vet[positionDelete].dailyPrice = -1;
			vet[positionDelete].days = -1;
			vet[positionDelete].totalPrice = -1;
			recordRegister(vet,tam);
			cout << endl << "Usuario deletado com sucesso. Retornando ao menu principal...\n\n";
		break;
		
		case 2:
			cout << endl << "Funcao cancelada. Retornando ao menu principal...\n\n";
		break;
	}
}

void registerMenu(userRegister vet[],int tam, int pos_i, int menuFunction){
	cout << "MENU DE CADASTRO\n";
	cout << "Por favor, digite os dados do cliente:\n";
	vet[pos_i].userId = (vet[pos_i-1].userId + 1);
	cout << "\n1. Nome: ";
	cin.ignore();
	getline(cin,vet[pos_i].userName);
	cout << "\n2. CPF: ";
	cin.ignore();
	getline(cin,vet[pos_i].cpf);
	cout << "\n3. Opcoes de quarto:\n";
	int room = -1;
	while ((room < 1) or (room > 5)){
		cout << "\n\t1.Suite: Standart.\n\t2.Suite: Confort.\n\t3.Suite: Executive.\n\t4.Suite: Luxury.\n\t5.Suite: Luxury Master.";
		cout << "\n\nQuarto escolhido: ";
		cin >> room;
		switch (room){
			case 1:
				vet[pos_i].dailyPrice = 100;
			break;
			
			case 2:
				vet[pos_i].dailyPrice = 150;
			break;
			
			case 3:
				vet[pos_i].dailyPrice = 200;
			break;
			
			case 4:
				vet[pos_i].dailyPrice = 250;
			break;
			
			case 5:
				vet[pos_i].dailyPrice = 300;
			break;
			
			default:
				cout << "\nOpcao de quarto invalida! Tente novamente.";
			break;
		}
	}
	cout << "\n4. Dias hospedado: ";
	cin >> vet[pos_i].days;
	vet[pos_i].totalPrice = (vet[pos_i].dailyPrice * vet[pos_i].days);
	cout << "\n4. Total a ser pago: R$" << vet[pos_i].totalPrice << endl << endl;
	cout << "Usuario cadastrado com sucesso! Retornando ao menu principal...";
	cout << endl << endl;
}

void orderId(userRegister vet[], int size) { //Ordenação por ID. Método utilizado: Shell Sort.
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;
    while (gaps[pos_gap] > size) {
        pos_gap--;
    }
    int value, j;
    while (pos_gap >= 0) {
        int gap = gaps[pos_gap];
        for (int i = gap; i < size; i++) {
            value = vet[i].userId;
            userRegister temp = vet[i];
            j = i;
            while ((j >= gap) and (value < vet[j - gap].userId)) {
                vet[j] = vet[j - gap];
                j = j - gap;
            }
            vet[j] = temp;
        }
        pos_gap--;
    }
}

void orderCPF(userRegister vet[], int size) { //Ordenação por CPF. Método utilizado: Shell Sort.
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;
    while (gaps[pos_gap] > size) {
        pos_gap--;
    }
    int j;
    string value;
    while (pos_gap >= 0) {
        int gap = gaps[pos_gap];
        for (int i = gap; i < size; i++) {
            value = vet[i].cpf;
            userRegister temp = vet[i];
            j = i;
            while ((j >= gap) and (value < vet[j - gap].cpf)) {
                vet[j] = vet[j - gap];
                j = j - gap;
            }
            vet[j] = temp;
        }
        pos_gap--;
    }
}

void orderMenu(userRegister vet[], int size){ //finalizar
	int orderOption = 0;
	cout << "MENU DE ORDENACAO \n";
	cout << "Deseja ordenar os usu�rios por: " << endl << "1- ID" << endl << "2- CPF \n";
	cin >> orderOption;
	if (orderOption != 1 or orderOption != 2) {
		cout << "Op��o invalida. Digite uma op��o valida: \n";
		cin >> orderOption; 
	}
	switch (orderOption) {
		case 1:
			orderId(vet, size);
			cout << "Ordena��o de clientes por ID efetuada com sucesso! Retornando ao menu principal... \n";
			break;
		
		case 2:
			orderCPF(vet, size);
			cout << "Ordena��o de clientes por CPF efetuada com sucesso! Retornando ao menu principal... \n";
			break; 
		
	}
}

int main() {
    int menuFunction = 100, searchFunction = 100, pos_add = -1;;
    bool archive = false;
    int n = 110;
	userRegister *vet = new userRegister[n];
	readRegister(vet,n,archive,menuFunction);
    if (not(archive)) {
        cout << "Arquivo nao encontrado!";
    } else {
		
		while (menuFunction != 0) {
			menuFunction = 100;
			searchFunction = 100;
			mainMenu(menuFunction);
			switch (menuFunction){
				case 1: 
					vet = allocationRegister(vet,n,menuFunction);
					printRegister(vet,n);
				break;
            
				case 2:
					while (searchFunction != 4) {
						searchMenu(searchFunction);
						if (searchFunction == 4){
							cout << "Retornando ao menu principal...\n\n";
							break;
						} else if (searchFunction == 0){
							cout << "Encerrando sistema...";
							menuFunction = 0;
							break;
						}
						search(vet, searchFunction, menuFunction,n);
					}
				break;

				case 3:
					pos_add = -1;
					searchEmpty(vet,pos_add,n);
					if (pos_add == -1){
						vet = addRegister(vet,n);
						vet[n-1].userId = -1;
						vet[n-1].userName = "-1";
						vet[n-1].cpf = "-1";
						vet[n-1].dailyPrice = -1;
						vet[n-1].days = -1;
						vet[n-1].totalPrice = -1;
						pos_add = n-1;
					}
					registerMenu(vet,n,pos_add,menuFunction);
					recordRegister(vet,n);
				break;

				case 4:
					deleteMenu(vet,n);
				break;
				
				case 5:
					
				case 0:
					cout << "Encerrando sistema...";
				break;

				default:
					cout << "Digite uma funcao valida.\n\n";
				break;
			}
		}
	}
    return 0;
}

