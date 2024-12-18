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

void listarTransacciones(){
    Transaccion transTemp;
    int len=0,paginaActual=0,opcion=0;
    string username;

    cout<<"Enter username: ";
    cin>>username;

    FILE* archivoTransacciones = fopen("transactions.dat","rb");
    while(fread(&transTemp,sizeof(Transaccion),1,archivoTransacciones)){
        if(transTemp.username==username){
            len++;
        }
    }
    fclose(archivoTransacciones);
    Transaccion transaccionesUsername[len],transaccionesPorPagina[len][5];

    archivoTransacciones = fopen("transactions.dat","rb");
    while(fread(&transTemp,sizeof(Transaccion),1,archivoTransacciones)){
        if(transTemp.username==username){
            transaccionesUsername[opcion]=transTemp;
            opcion++;
        }
    }
    fclose(archivoTransacciones);
    
    if(transaccionesUsername[0].id==0){
        system("cls");
        cout<<"The entered user has no transactions."<<endl;
        return;
    }
    for(int i=0;i<=len/5.001;i++){
        for(int j=0;j<5&&(((len-1)-(j+i*5))>=0);j++){
            if((len-1)-(j+i*5)>=0){
                transaccionesPorPagina[i][j]=transaccionesUsername[(len-1)-(j+i*5)];
            }
        }
    }
    
    while(true){
        system("cls");
        cout<<"Showing transactions from most recent to oldest of "<<username<<".\nPage "<<paginaActual+1<<" of "<<int(len/5.001)+1<<endl<<endl;
        
        for(int i=0; i<len-5*paginaActual && i<5 ;i++){
            cout<<
            "Transaction ID: "<<transaccionesPorPagina[paginaActual][i].id<<
            "\tDate: "<<transaccionesPorPagina[paginaActual][i].fecha<<
            "\t   Type: "<<transaccionesPorPagina[paginaActual][i].tipo<<
            "\tAmount: "<<transaccionesPorPagina[paginaActual][i].monto<<endl;
        }
        opcion=-1;
        while(paginaActual!=opcion){
            cout<<endl<<"0-Exit | (1-"<<int(len/5.001)+1<<") Navigate between pages\nEnter page number: ";
            cin>>opcion;
            switch(opcion){
            case 0:
                system("cls");
                cout<<"Exiting the list."<<endl<<endl;
                return;
            default:
                if(opcion>int(len/5.001)+1||opcion<0){
                    cout<<"ERROR. You must enter a number between 0 and "<<int(len/5.001)+1<<endl<<endl;
                } else{
                    opcion--;
                    paginaActual=opcion;
                    break;
                }
            }
        }
    }
}

void ingresosEgresos(){
    Transaccion transTemp;
    string username,meses[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int totalIngresos=0,totalEgresos=0,fechatemp=0;

    cout<<"Enter username: ";
    cin>>username;
    system("cls");
    
    FILE* archivoTransacciones = fopen("transactions.dat","rb+");

    while(fread(&transTemp,sizeof(Transaccion),1,archivoTransacciones)){
        if(transTemp.username==username){
            if(fechatemp!=0 && transTemp.fecha/100!=fechatemp){
                cout<<endl<<fechatemp/100<<" - "<<meses[(fechatemp%100)-1]<<endl;
                cout<<"Total amount of Income: "<<totalIngresos<<endl;
                cout<<"Total amount of Expenses: "<<totalEgresos<<endl;
                totalIngresos=0;
                totalEgresos=0;
            }
            fechatemp=transTemp.fecha/100;
            if(transTemp.tipo=='i'){
                totalIngresos+=transTemp.monto;
            } else {
                totalEgresos+=transTemp.monto;
            }
        }
    }
    if(fechatemp!=0){
        cout<<endl<<fechatemp/100<<" - "<<meses[(fechatemp%100)-1]<<endl;
        cout<<"Monto total Ingresos: "<<totalIngresos<<endl;
        cout<<"Monto total Egresos: "<<totalEgresos<<endl<<endl;
    } else{
        cout<<"The entered user has no transactions."<<endl;
    }

    fclose(archivoTransacciones);
}

void usernameAlArray(string usernames[],string username,int &len){
    for(int i=0;i<len;i++){
        if(username==usernames[i]){
            return;
        }
    }
    usernames[len]=username;
    len++;
}

void mostrarMaximos(){
    Transaccion transTemp;
    int len=0,montoMaximo,fechaMaximo;
    Cliente clienTemp;

    FILE* archivo2 = fopen("customers.dat","rb");
    while(fread(&clienTemp,sizeof(Cliente),1,archivo2)){
        len++;
    }
    fclose(archivo2);

    string usernames[len];
    len=0;

    FILE* archivo = fopen("transactions.dat","rb");

    while(fread(&transTemp,sizeof(Transaccion),1,archivo)){
        usernameAlArray(usernames,transTemp.username,len);
    }
    system("cls");
    cout<<"Maximum income per client: "<<endl<<endl;
    for (int i = 0; i < len; i++){
        montoMaximo=0;
        fseek(archivo,0,SEEK_SET);
        while (fread(&transTemp,sizeof(Transaccion),1,archivo)){
            if(usernames[i]==transTemp.username&&transTemp.tipo=='i'&&transTemp.monto>montoMaximo){
                montoMaximo=transTemp.monto;
                fechaMaximo=transTemp.fecha;
            }
        }
        if(montoMaximo!=0){
            cout<<"Username: "<<usernames[i]<<
            "\t   Date: "<<fechaMaximo%100<<"/"<<fechaMaximo/100%100<<"/"<<fechaMaximo/10000<<
            "\tMaximum Income: "<<montoMaximo<<endl;
        }
    }
}

void ingresosMaximos(){
    Transaccion transTemp;
    string username;
    int ingresosMaximos=0,sumaTemp=0,fechaMin=0,len=0;
    Cliente clienTemp;
    
    FILE* archivo2 = fopen("customers.dat","rb");
    while(fread(&clienTemp,sizeof(Cliente),1,archivo2)){
        len++;
    }
    fclose(archivo2);

    string usernames[len];
    len=0;

    FILE* archivo = fopen("transactions.dat","rb");
    fseek(archivo,-sizeof(Transaccion),SEEK_END);
    fread(&transTemp,sizeof(Transaccion),1,archivo);
    fseek(archivo,0,SEEK_SET);
    fechaMin=transTemp.fecha;

    if(fechaMin%100!=31){
        if(fechaMin/100%100-1<1){
            fechaMin=fechaMin-10000-fechaMin%10000+1100+30-fechaMin%100;
        }else{
            fechaMin=fechaMin-100-fechaMin%100+30-fechaMin%100;
        }
    }else{
        fechaMin-=30;
    }

    while(fread(&transTemp,sizeof(Transaccion),1,archivo)){
        if(fechaMin<transTemp.fecha){
            usernameAlArray(usernames,transTemp.username,len);
        }
    }

    fseek(archivo,0,SEEK_SET);
    for(int i=0;i<len;i++){
        sumaTemp=0;
        fseek(archivo,0,SEEK_SET);
        while(fread(&transTemp,sizeof(Transaccion),1,archivo)){
            if(fechaMin<transTemp.fecha&&transTemp.username==usernames[i]){
                if(transTemp.tipo=='i'){
                    sumaTemp+=transTemp.monto;
                }else{
                    sumaTemp-=transTemp.monto;
                }
            }
        }
        if(ingresosMaximos<sumaTemp){
            username=usernames[i];
            ingresosMaximos=sumaTemp;
        }
    }
    system("cls");
    cout<<"Client with the highest income in the last 30 days:\nUser: "<<username<<"\tIncome: "<<ingresosMaximos<<endl<<endl;
}

int main(){
    int opcion;

    FILE* archivo = fopen("transactions.dat","rb");

    if (!archivo){
        cout<<"ERROR. The transactions.dat file is missing."<<endl;
        return 0;
    }
    fclose(archivo);

    while(true){
        cout<<"\n0- Exit."<<endl<<
        "1- User Transactions."<<endl<<
        "2- Monthly income and expenses by User."<<endl<<
        "3- Maximum income per Client."<<endl<<
        "4- Client with the highest income in the last 30 days."<<endl<<
        "Enter what you want to do:";
        cin>>opcion;
        switch(opcion){
            case 0: return 0;
            case 1: 
                listarTransacciones();
                break;
            case 2:
                ingresosEgresos();
                break;
            case 3:
                mostrarMaximos();
                break;
            case 4:
                ingresosMaximos();
                break;
        }
    }
}