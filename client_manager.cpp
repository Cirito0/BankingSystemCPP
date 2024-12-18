//GESTOR DE CLIENTES
#include <iostream>

using namespace std;

struct Cliente{
    char nombre[50];
    int dni;
    char username[50];
    char pass[50];
    int saldo=0;
};

bool verificador(string username){
    Cliente clientemp;

    FILE* archivo = fopen("clientes.dat","rb");

    if(!archivo){
        archivo = fopen("clientes.dat","wb");
    }
    
    while(fread(&clientemp,sizeof(Cliente),1,archivo)){
        if(clientemp.username==username){
            fclose(archivo);
            return false;
        }
    }
    fclose(archivo);
    return true;
}

bool verificador(int dni){
    Cliente clientemp;

    FILE* archivo = fopen("clientes.dat","rb");
    while(fread(&clientemp,sizeof(Cliente),1,archivo)){
        if(clientemp.dni==dni){
            fclose(archivo);
            return false;
        }
    }
    fclose(archivo);
    return true;
}

void pedirDatosCliente(Cliente &cliente){
    cout<<"Enter your name: ";
    cin>>cliente.nombre;

    while(true){
        cout<<"Enter your username: ";
        cin>>cliente.username;
        if (!verificador(cliente.username)){
            cout<<"ERROR. This username is already taken."<<endl<<endl;
        } else{
            break;
        }
    }
    
    while(true){
        cout<<"Enter your ID: ";
        cin>>cliente.dni;

        if(cliente.dni>0){
            if (!verificador(cliente.dni)){
                cout<<"\nERROR. This ID is already taken."<<endl<<endl;
            } else{
                break;
            }
        }else{
            cout<<"ERROR. Invalid ID.\n\n";
        }
    }

    cout<<"Enter your password: ";
    cin>>cliente.pass;
}

void agregarCliente(Cliente nuevo_cliente){
    FILE* archivo = fopen("clientes.dat","rb+");
    fseek(archivo,0,SEEK_END);
    fwrite(&nuevo_cliente,sizeof(Cliente),1,archivo);
    fclose(archivo);
}

int main(){
    Cliente nuevo_cliente;
    system("cls");
    cout<<"Welcome to the customers sign up.\n\n";

    pedirDatosCliente(nuevo_cliente);
    nuevo_cliente.saldo+=10000;

    
    agregarCliente(nuevo_cliente);

    return 0;
}