#include<iostream>

using namespace std;


int main(){
    cout<<"Enter No of resources:";
    int resource=0;
    cin>>resource;


    cout<<"Enter No of Processes:";
    int processes=0;
    cin>>processes;

    int i,j;
    int total_instance[resource];
    for ( i = 0; i < resource; i++)
    {
        cout<<"Enter No. of total instance of Resource "<<i+1<<": ";
        cin>>total_instance[i];
    }

    cout<< "\nEnter allocated instance of resources to each process (Allocation Matrix):-"<<endl;
    int allocation[processes][resource];
    for ( i = 0; i < processes; i++)
    {
        for ( j = 0; j < resource; j++)
        {
            cin>>allocation[i][j];
        }
    }

    cout<< "\nEnter Maximum instance of resources a process can call (Max Matrix):-"<<endl;
    int max[processes][resource];
    for ( i = 0; i < processes; i++)
    {
        for ( j = 0; j < resource; j++)
        {
            cin>>max[i][j];
        }
    }

    cout<< "\nAfter allocation how much resources are still needed to a Process (Need Matrix):-"<<endl;
    int need[processes][resource];
    for ( i = 0; i < processes; i++)
    {
        cout<<"for process "<<i+1<<"    ";
        for ( j = 0; j < resource; j++)
        {
            need[i][j] = max[i][j]-allocation[i][j];
            cout<<need[i][j]<<" ";
        }
        cout<<"\n";
    }

    int total_allocated[resource];
    for ( i = 0; i < resource; i++)
    {
        total_allocated[i]=0;
    }
    for ( i = 0; i < processes; i++)
    {
        for ( j = 0; j < resource; j++)
        {
            //cout<< allocation[i][j]<<  " ";
            total_allocated[j] = total_allocated[j] + allocation[i][j];
        }
    }

    cout<<"Total allocated instances of each resouces: ";
    for ( i = 0; i < resource; i++)
    {
        cout<<total_allocated[i]<<" ";
    }
    cout<<"\n";

    cout<<"Avialible resources after alloction: ";
    int avail[resource];
    for ( i = 0; i < resource; i++)
    {
        avail[i] = total_instance[i] - total_allocated[i];
        cout<<avail[i]<<" ";
    }


    bool process_completed[processes],flag;
    int process_done[processes],index=0;

    for ( i = 0; i < processes; i++)
    {
        process_completed[i]=false;
    }

    start:

        for ( i = 0; i < processes; i++)
        {
            if (process_completed[i]==false)
            {
                flag=false;
                for ( j = 0; j < resource; j++)
                {
                    if (need[i][j]<=avail[j])
                    {
                        flag=true;
                    }
                }
                if (flag==true)
                {
                    process_completed[i]=true;
                    for ( j = 0; j < resource; j++)
                    {
                        avail[j]+=allocation[i][j];
                    }
                    // here loop is needed
                    process_done[index]=i+1;
                    index++;
                    cout<<"\nprocessing...\nprocess done: p"<<i+1<<endl;
                    cout<<"now Avilable resources:";
                    for ( j = 0; j < resource; j++)
                    {
                        cout<<avail[j]<<" ";
                    }
                }
            }
        }
        
    for ( i = 0; i < processes; i++)
    {
        if (process_completed[i]==false && flag==true)
        {
            //cout<<"\n1\n";
            goto start;
        }
    }

    for ( i = 0; i < processes; i++)
    {
        if (process_completed[i]==false && flag==false){
            cout<<"\nPANIC: SYSTEM IS IN UNSAFE STATE!!"<<endl;
            cout<<"Current avilable instances of resources:";
            for ( i = 0; i < resource; i++)
            {
                cout<<avail[i]<<" ";
            }
            cout<<"\nResource need of remaing processes:-\n";
            for ( j = 0; j < processes; j++)
            {
                if (process_completed[i]==false)
                {
                    int k;
                    for ( k = 0; k < resource; k++)
                    {
                        cout<<need[j][k]<<" ";
                    }   
                }
                cout<<"\n";
            }
            
        }
    }

    bool flag3 = false;
    for ( i = 0; i < processes; i++)
    {
        if (process_completed[i]==true)
        {
            flag3=true; 
        }
    }
    if (flag3==true)
    {
        cout<<"\nAll processes executed successfully!"<<endl;
        cout<<"Safe Sequence of processes is:";
        for ( i = 0; i < processes; i++)
        {
            cout<<"p"<<process_done[i]<<"  ";
        }  
    }
    cout<<"\n";
}
