//GENERADOR
#include<iostream>

using namespace std;

struct Cliente{
    char nombre[50];
    int dni;
    char username[50];
    char pass[50];
    int saldo=0;
};

struct Transaccion {
    int id=0;
    char username[50];
    int monto;
    char tipo;
    int fecha=0;
};

Cliente validacionIdentidad(){
    Cliente temp;
    string username,pass;
    int intentos;
    bool encontrado;
      
    FILE* archivoClientes = fopen("clientes.dat","rb+");

    while(true){
        intentos=3;
        encontrado=0;

        while(encontrado==0){
            fseek(archivoClientes,0,SEEK_SET);
            cout<<"Enter your username: ";
            cin>>username;

            while(fread(&temp,sizeof(Cliente),1,archivoClientes)){
                if(temp.username==username){
                    encontrado=1;
                    break;
                }
            }

            if(encontrado==0){
                system("cls");
                cout<<"Username not found.\n\n";
            }
        }
        
        while(intentos>0){
            cout<<"Enter your password: ";
            cin>>pass;
            if(pass==temp.pass){
                system("cls");
                cout<<"Password correct. Accessing system.\n\n";
                fclose(archivoClientes);
                return temp;
            } else{
                intentos--;
                cout<<"Password Incorrect. You have "<<intentos<<" attempt(s) remaining.\n\n";
            }
        }
        system("cls");
        cout<<"You've ran out of attempts.\n\n";
    }
}

void guardarCliente(Cliente perfil){
    string usernameBuscado=perfil.username;
    Cliente clienTemp;
    FILE* archivoClientes = fopen("clientes.dat","rb+");
    while(fread(&clienTemp,sizeof(Cliente),1,archivoClientes)){
        if(clienTemp.username==usernameBuscado){
            break;
        }
    }
    fseek(archivoClientes,-sizeof(Cliente),SEEK_CUR);
    fwrite(&perfil,sizeof(Cliente),1,archivoClientes);
    fclose(archivoClientes);
}

void generarTransaccion(Cliente &perfil,int multiplicador){
    Transaccion trans;
    int fechaTrans=0,montoTrans;
    string texto[]={"withdraw","","deposit"};

    cout<<"How much money do you want to "<<texto[multiplicador+1]<<"? -> $";
    cin>>montoTrans;
    
    if((perfil.saldo + montoTrans * multiplicador)<0){
        system("cls");
        cout<<"ERROR. You do not have sufficient balance.\n";
        return;
    } else if(montoTrans<=0){
        system("cls");
        cout<<"ERROR. The amount cannot be less than or equal to 0.\n";
        return;
    }
    
    perfil.saldo += montoTrans*multiplicador;

    FILE* archivoTransacciones = fopen("transacciones.dat","rb+");

    if(!archivoTransacciones){
        archivoTransacciones = fopen("transacciones.dat","wb");
    }

    fseek(archivoTransacciones,-sizeof(Transaccion),SEEK_END);
    fread(&trans,sizeof(Transaccion),1,archivoTransacciones);
    
    trans.id++;
    trans.monto=montoTrans;


    while(fechaTrans<10000000||fechaTrans>99999999||
        fechaTrans/100%100<1||fechaTrans/100%100>12||
        fechaTrans%100<1||fechaTrans%100>31
        ){
        cout<<"\nEnter the date of your transaction in the format YYYYMMDD.";
        if(trans.fecha!=0){
            cout<<" (Last recorded date:" <<trans.fecha/100%100<<"/"<<trans.fecha%100<<"/"<<trans.fecha/10000<<"): ";
        } else {
            cout<<": ";
        }
        cin>>fechaTrans;
        trans.fecha=fechaTrans;
        if((fechaTrans<10000000)||(fechaTrans>99999999)){
            system("cls");
            cout<<"ERROR. The entered date must be in the format YYYYMMDD."<<endl<<endl;
        }else if(fechaTrans/100%100<1||fechaTrans/100%100>12){
            cout<<"ERROR. Nonexistent month."<<endl;
        }else if(fechaTrans%100<1||fechaTrans%100>31){
            cout<<"ERROR. Nonexistent day."<<endl;
        }
    }
    trans.fecha=fechaTrans;

    if(multiplicador==1){
        trans.tipo='i';
    } else{
        trans.tipo='e';
    }

    for(int i=0;perfil.username[i-1]!='\0';i++){
        trans.username[i] = perfil.username[i];
    }
    
    fseek(archivoTransacciones,0,SEEK_END);
    fwrite(&trans,sizeof(Transaccion),1,archivoTransacciones);
    fclose(archivoTransacciones);
    guardarCliente(perfil);

    system("cls");
    cout<<"Transaction created. ID: "<<trans.id<<".\n";
}

void eliminarTransPorID(string username,int idEliminar){
    Transaccion transAux;
    bool encontrada=0;

    system("cls");

    FILE* archivoTransacciones = fopen("transacciones.dat","rb");
    FILE* archivoTemporal = fopen("temporal.dat","wb");

    while(fread(&transAux,sizeof(Transaccion),1,archivoTransacciones)){
        if(transAux.id!=idEliminar){
            fwrite(&transAux,sizeof(Transaccion),1,archivoTemporal);
        }else{
            if(transAux.username==username){
                encontrada=1;
            }else{
                cout<<"ERROR. The transaction with that ID does not belong to your user.\n";
                fclose(archivoTransacciones);
                fclose(archivoTemporal);
                remove("temporal.dat");
                return;
            }
        }
    }
    if(encontrada==0){
        cout<<"ERROR. No transaction exists with that ID.\n";
    } else{
        cout<<"Transaction with ID "<<idEliminar<<" deleted.\n";
    }
    fclose(archivoTransacciones);
    fclose(archivoTemporal);
    remove("transacciones.dat");
    rename("temporal.dat","transacciones.dat");
}

int main(){
    Cliente perfil;
    int opcion,idEliminar;

    FILE* archivo = fopen("clientes.dat","rb");

    if(!archivo){
        cout<<"ERROR. The clientes.dat file is missing."<<endl;
        return 0;
    }
    fclose(archivo);

    perfil=validacionIdentidad();

    cout<<"Welcome "<<perfil.nombre<<". ";
    
    while(true){
        //cout<<"Su saldo es $"<<perfil.saldo<<".\n\n0- Salir.\n1- Ingresar dinero.\n2- Retirar dinero.\n3- Eliminar Transaccion por ID.\n\nSeleccione su opcion: ";
        cout<<"Your balance is $"<<perfil.saldo<<".\n\n0- Exit.\n1- Deposit money.\n2- Withdraw money.\n3- Delete transaction by ID.\n\nSelect your option:";
        cin>>opcion;
        switch(opcion){
            case 0:
                return 0;
            case 1:
                generarTransaccion(perfil,1);
                break;
            case 2:
                generarTransaccion(perfil,-1);
                break;
            case 3:
                cout<<"Please indicate the transaction ID to delete -> ";
                cin>>idEliminar;
                eliminarTransPorID(perfil.username,idEliminar);
                break;
            default:
                system("cls");
                cout<<"Nonexistent option.\n";
        }
    }
    return 0;
}