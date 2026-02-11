#include <iostream>
using namespace std;

struct SNode{
    int id;
    SNode * SNext;
};

struct CNode{
    int code;
    CNode * CNext;
    SNode *stu_list;
};

CNode *CList = NULL;

void insertCourse(int code){
    CNode* temp;
    temp = (CNode *)malloc(sizeof(CNode));
    temp->code = code;
    temp->CNext = NULL;
    temp->stu_list = NULL;

    if (CList == NULL){
        CList = temp;
        return;
    }

    CNode* cur = CList;
    while (cur->CNext != NULL)
        cur = cur->CNext;

    cur->CNext = temp;
}


// void insertStudent(int id, int code){
//     CNode* Ccurr= CList;
//     while(Ccurr!=NULL){
//         if (code == Ccurr->code){
//             SNode* temp;
//             temp = (SNode*)malloc(sizeof(SNode));
//             temp->id=id;
//             temp->SNext = NULL;

//             if (Ccurr->stu_list==NULL){
//                 Ccurr->stu_list=temp;
//                 return;
//             }
//             else{
//                 SNode* Scurr = Ccurr->stu_list;
//                 while(Scurr->SNext != NULL)
//                     Scurr = Scurr->SNext;
//                 Scurr->SNext = temp;
//             }
//             return;
//         }
//     }
//     Ccurr = Ccurr->CNext;
// }

void insertStudent(int id, int code){
    CNode* Ccurr = CList;

    while (Ccurr != NULL){
        if (code == Ccurr->code){

            SNode* temp;
            temp = (SNode*)malloc(sizeof(SNode));
            temp->id = id;
            temp->SNext = NULL;

            if (Ccurr->stu_list == NULL){
                Ccurr->stu_list = temp;
            }
            else{
                SNode* Scurr = Ccurr->stu_list;
                while (Scurr->SNext != NULL)
                    Scurr = Scurr->SNext;
                Scurr->SNext = temp;
            }
            return;
        }
        Ccurr = Ccurr->CNext;
    }

    cout << "Course is not available\n";
}


void displayAll(){
    CNode* Ccurr = CList;

    while (Ccurr != NULL){
        cout << "course: " << Ccurr->code << endl;
        cout << "students ";

        SNode* Scurr = Ccurr->stu_list;
        if (Scurr == NULL){
            cout << "Student list is empty";
        }
        else{
            while (Scurr != NULL){
                cout << Scurr->id << " ";
                Scurr = Scurr->SNext;
            }
        }

        cout << "\n\n";
        Ccurr = Ccurr->CNext;
    }
}
int main(){

    insertCourse(451);
    insertCourse(362);

    insertStudent(87, 451);
    insertStudent(7, 451);
    insertStudent(87, 362);

    displayAll();

    return 0;
}
