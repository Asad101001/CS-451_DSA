#include<iostream>
#include<stdlib.h>
using namespace std;

struct SNode 
{
    int SNo; 
    SNode * Snext; 
    SNode * stu_list; 

};

struct CNode 
{
    int CNo;
    CNode * Cnext;  
    SNode * stu_list;

};

CNode*Clist=NULL;  

void insert_course(int value)
{
    CNode*temp;  
    temp=(CNode*)malloc(sizeof(CNode));
    temp->CNo=value; 
    temp->Cnext=NULL;  
    
    temp->stu_list=NULL; 

    if (Clist==NULL)
    {
        Clist=temp;
    }
    else
    {
        CNode*Ccurr=Clist; 
        while(Ccurr->Cnext!=NULL) 
        {
            Ccurr=Ccurr->Cnext; 
        }
        Ccurr->Cnext=temp;
    }


}

void search_course(int value)
{
    CNode*Ccurr=Clist;
    while(Ccurr!=NULL)
    {
        if(Ccurr->CNo==value)
        {
            cout<<"Value found: "<<value<<endl;
            return;
        }
        Ccurr=Ccurr->Cnext;
    }
    cout<<"Value not found: "<<value<<endl;
 
    
}


void search_stu_in_course(int course,int seat)
{
    CNode*Ccurr=Clist;
    bool found=false;

    if(Ccurr==NULL)
    {
        cout<<"Course List is empty, Search is not possible"<<endl;
        return;
    }
    
    while(Ccurr!=NULL) 
    {
        
        
        if(course==Ccurr->CNo) 
        {
            
            SNode*Scurr=Ccurr->stu_list;
            

            if (Scurr==NULL)
            { 
                cout<<"Student list is empty in the course, search not possible";
                return;
            }

            if (seat==Scurr->SNo) 
            {
               cout<< "Student found of seat number: "<<seat<<" in course number: "<<course<<endl;
               found=true;
               return;
            }
        
            
            Scurr=Scurr->Snext; 
           
            while (Scurr!=NULL) 
            {
                if(Scurr->SNo==seat) 
                {
                    
                    cout<< "Student found of seat number: "<<seat<<" in course number: "<<course<<endl;
                    found=true;
                    return;
                }
 
                Scurr=Scurr->Snext;
            }   

            if (found!=true)
            {
                cout<<"Student not found of seat number: "<<seat<<endl;
            }
        }
        Ccurr=Ccurr->Cnext;
    }
 
    
}

void search_student(int seat)
{
    CNode*Ccurr=Clist;
    bool found=false;
    int count=0;

    if(Ccurr==NULL)
    {
        cout<<"Course List is empty, Search is not possible"<<endl;
        return;
    }
    
    while(Ccurr!=NULL) 
    {
        SNode*Scurr=Ccurr->stu_list;

        while(Scurr!=NULL)
        {
        
        

                if (Scurr==NULL)
                { 
                    cout<<"Student list is empty in the course, search not possible";
                    return;
                }
                
                while(Scurr!=NULL){

                    if (seat==Scurr->SNo) 
                    {
                        found=true;
                        count++;
                        
                        
                    }
                    Scurr=Scurr->Snext;
                }

            }
            Ccurr=Ccurr->Cnext;
        }
        
    if (found!=true)
        {
            cout<<"Student not found of seat number: "<<seat<<endl;
        }
    cout<< "Student found of seat number "<<seat<<" in "<<count<<" courses."<< endl;
    return;
 
    
}




void display_course()
{
    CNode*Ccurr=Clist;
    if (Clist!=NULL)
    {
        while(Ccurr!=NULL)
        {
            
            cout<<Ccurr->CNo<<" ";
            Ccurr=Ccurr->Cnext;
        }
        cout<<endl;
    }
    else
    {
        cout<<"List is empty"<<endl;
    }
}

void insert_stu(int val1, int val2) 
{
    CNode* Ccurr=Clist;
    while (Ccurr != NULL)
    {

        if (val1==Ccurr->CNo)
        {
            SNode*temp;
            temp=(SNode*)malloc(sizeof(SNode));
            temp->SNo=val2;
            temp->Snext=NULL;

            if (Ccurr->stu_list==NULL) 
            {
                Ccurr->stu_list=temp;  
                return;

            }
            else
            {
                SNode*Scurr=Ccurr->stu_list; 
                                             

                while(Scurr->Snext!=NULL) 
                {
                    Scurr=Scurr->Snext; 
                }
                Scurr->Snext=temp; 
            }
            return;

        }
        Ccurr=Ccurr->Cnext; 
    }

    return; 
}


void Delete_student_from_a_course(int course,int seat)
{
    CNode*Ccurr=Clist;


    if(Ccurr==NULL)
    {
        cout<<"Course List is empty, deletion not possible"<<endl;
        return;
    }
    
    while(Ccurr!=NULL) 
    {
        
        
        if(course==Ccurr->CNo) 
        {
            
            SNode*Scurr=Ccurr->stu_list; 
            SNode*prev=NULL;

            if (Scurr==NULL)
            { 
                cout<<"Student list is empty in the course";
                return;
            }

            if (seat==Scurr->SNo) 
            {
                
                Ccurr->stu_list=Ccurr->stu_list->Snext; 

                free(Scurr); 
                cout<<"Student deleted: "<<seat;
                return;
            }
        
            
            Scurr=Scurr->Snext; 
            
            prev=Ccurr->stu_list; 
           
            while (Scurr!=NULL) 
            {
                if(Scurr->SNo==seat) 
                {
                    prev->Snext=Scurr->Snext;  
                    
                    free(Scurr);
                    cout<<"Student deleted of seat number: "<<seat<<endl;
                    return;
                }
                prev=Scurr;
                Scurr=Scurr->Snext;
            }   
            cout<<"Student not found: "<<seat<<endl;
        }
        Ccurr=Ccurr->Cnext;
    }
}


void Delete_student2(int seat)
{
    CNode*Ccurr=Clist;



    if(Ccurr==NULL)
    {
        cout<<"Course List is empty, deletion not possible"<<endl;
        return;
    }
    
    while(Ccurr!=NULL) 
    {
        
        
        
            
            SNode*Scurr=Ccurr->stu_list; 
            SNode*prev=NULL;

            if (Scurr==NULL) // if the stu list is empty 
            { 
                cout<<"Student list is empty in the course";
                return;
            }


            int count = 0;
            
                while(Ccurr!=NULL & seat==Scurr->SNo) 
                {


                    count++; 
                    Ccurr->stu_list=Ccurr->stu_list->Snext; 
                    
                    free(Scurr); 

                    Ccurr=Ccurr->Cnext; 
                    if (Ccurr!=  NULL) 
                    {
                        Scurr=Ccurr->stu_list; 
                    }
                    else{
                        cout<<"Student deleted of seat number: "<<seat<<" from all the available "<<count<<" courses!";
                        return;
                    }
                    
                }
                

            
        
            
            Scurr=Scurr->Snext; // moves forward the scurr to the second elemnt
            
            prev=Ccurr->stu_list; // prev points to the stu_list

        Ccurr=Ccurr->Cnext;
    }
}






void Delete_student(int seat)
{
    CNode* Ccurr = Clist;
   

    if (Ccurr == NULL)
    {
        cout << "Course List is empty, deletion not possible" << endl;
        return;
    }

    while (Ccurr != NULL)
    {
        SNode* Scurr = Ccurr->stu_list;
        SNode* prev = NULL;

        while (Scurr != NULL)
        {
            if (Scurr->SNo == seat)
            {
                SNode* temp = Scurr; // Store node to free it later
                
                if (prev == NULL) // Case: Student is at the head
                {
                    Ccurr->stu_list = Scurr->Snext;
                    Scurr = Ccurr->stu_list; // Move Scurr to the new head
                }
                else // Case: Student is in the middle or end
                {
                    prev->Snext = Scurr->Snext;
                    Scurr = prev->Snext; // Move Scurr to the next valid node
                }

                free(temp);
                cout << "Student deleted from Course " << Ccurr->CNo << " : " << seat << endl;
               
                continue; 
            }

            prev = Scurr;
            Scurr = Scurr->Snext;
        }
        Ccurr = Ccurr->Cnext;
    }

 
}

void Delete_course(int value)
{
    CNode*Ccurr=Clist;
    CNode*prev=NULL;
    


    if(Ccurr==NULL)
    {
        cout<<"Course List is empty, deletion not possible"<<endl;
        return;
    }
    

    
    while(Ccurr!=NULL) // this for the loop to run until the Ccurr is not null for the course traversing
    {
        
        
        if (value==Ccurr->CNo) // first case if the value matches the first course in the list
        {
            Clist=Clist->Cnext; // joins the course list to the second elemnt
            SNode* Scurr = Ccurr->stu_list; // scurr points to the stu_list
           
            while(Scurr!=NULL) // iterates until the scurr is not null
            {
                Ccurr->stu_list=Ccurr->stu_list->Snext;  //joins the stu list to the list's second elemnt

                free(Scurr); // frees the scurr which is in first run is at first elemnt

                Scurr= Ccurr->stu_list; // points the scurr again at the list's first elemnt so that the elemnt deletion is always from the first element
                // Scurr=Scurr->Snext;
            }
            free(Ccurr); // when the scurr is null and all the students gets deleted the Ccurr is now freed
            return; // returned from here so that now the Ccurr is not moved to the next
        }           

        prev=Clist;
        Ccurr=Ccurr->Cnext;

        while (Ccurr !=NULL)
        {
            if (value==Ccurr->CNo)
            {
                prev->Cnext=Ccurr->Cnext;
                SNode* Scurr = Ccurr->stu_list;

                while(Scurr!=NULL) // iterates until the scurr is not null
                {
                    Ccurr->stu_list=Ccurr->stu_list->Snext; 

                    free(Scurr); // frees the scurr which is in first run is at first elemnt

                    Scurr= Ccurr->stu_list; 

                }
                free(Ccurr); // when the scurr is null and all the students gets deleted the Ccurr is now freed
                return;
            }
            prev=Ccurr;
            Ccurr=Ccurr->Cnext;
        }
            
    }

}



void display_all()
{
    CNode*Ccurr=Clist;
    if (Clist!=NULL)
    {
        while(Ccurr!=NULL) // while loop for the course lists
        {
            
            cout<<"\nThe course number "<<Ccurr->CNo<<endl;
            
            SNode*Scurr=Ccurr->stu_list;
            cout<<"The roll number of students enrolled in this course are:\n";

                while(Scurr!=NULL) // another while loop for the student list
                {
                    cout<<Scurr->SNo<<"\n";
                    Scurr=Scurr->Snext;
                }
                
                Ccurr=Ccurr->Cnext;
            // }

            
        }
        cout<<endl;
    }
    else
    {
        cout<<"List is empty"<<endl;
    }
}




int main()
{
    int choice, val,num,val1,val2;
    string state; 
    
    while (true)
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Insert course \n2. Insert student \n3. Search Course \n4. Search student  \n5. Search a student in a course  \n6. Delete a course \n7. Delete Student from a course \n8. Delete student \n9. Delete student 2nd Edition \n10. Display All \n11. Display Courses  \n12. Exit \n";
        cout << "Enter choice: ";
        cin >> choice; 
        
        switch(choice) 
        {
            case 1:
                
                while(true)
                    {
                        cout << "Enter the course: ";
                        cin >> val;
                        insert_course(val);

                        cout<<"Do you want to add more courses? y/n"<<endl;
                        cin>>state;
                        if (state!="y")
                        {
                            break;
                        }
                    
                    }
                    break;
            
            case 2:

                while(true)
                {
                    int val1,val2;
                    cout<<"Enter the course number you want the student to enroll: ";
                    cin>>val1;
                    cout<<"Enter the seat number of the student: ";
                    cin>>val2;
                    insert_stu(val1,val2);

                    cout<<"Do you want to add more students? y/n"<<endl;
                    cin>>state;
                    if (state!="y")
                    {
                        break;
                    }
                }
                break;
                

            case 3:
                
                cout << "Enter value to search: ";
                cin >> num;
                search_course(num);
                break;


            case 4:

                while(true)
                {
                    cout << "Enter the seat number to search a student: ";
                    cin >> val1;

                    search_student(val1);
                    cout<<"Do you want to search more students? y/n"<<endl;
                    cin>>state;
                    if (state!="y")
                    {
                        break;
                    }
                }
                break;

            case 5:

                while(true)
                {
                    cout << "Enter the course from which you want to search a student: ";
                    cin >> val1;
                
                    cout << "Enter the seat number to search a student: ";
                    cin >> val2;

                    search_stu_in_course(val1,val2);
                    cout<<"Do you want to search more students? y/n"<<endl;
                    cin>>state;
                    if (state!="y")
                    {
                        break;
                    }
                }
                break;


            case 6:

                cout << "Enter the course to be deleted: ";
                cin >> val1;
                Delete_course(val1);
                break;


                cout << "Enter the course from which you want to delete a student: ";
                cin >> val1;
            
                cout << "Enter the seat number of the student to be deleted: ";
                cin >> val2;
                Delete_student_from_a_course(val1,val2);
                break;

            case 7:

                cout << "Enter the course from which you want to delete a student: ";
                cin >> val1;
            
                cout << "Enter the seat number of the student to be deleted: ";
                cin >> val2;
                Delete_student_from_a_course(val1,val2);
                break;




            case 8:


                cout << "Enter the seat number of the student to be deleted: ";
                cin >> val1;
                Delete_student(val1);
                break;

               
            case 9:

                cout << "Enter the seat number of the student to be deleted: ";
                cin >> val1;
                Delete_student2(val1);
                break;


                
            case 10:

                display_all();
                break;



            case 11:

                display_course();
                break;


            case 12:
                exit(0);
                break;


            

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;

}