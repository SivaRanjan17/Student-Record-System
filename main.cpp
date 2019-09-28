#include<iostream>
#include<string>
#include<map>

using namespace std;
struct node
{
       int class_rank;
       string name;
       int roll_no;
       int marks;
       node *parent;
       char color;
       node *left;
       node *right;
       node *rno;
};
int c=0;
map<int,node*>rno_node;

class RBtree
{
      node *root;
      node *q;
   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }

      void Insert();
      void Recolor(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void FindRank();
      void Inorder(node*);
      void displayRank();
      void display1();
      void displayInorder1(node*);
      void display2();
      void displayInorder2(node*);
      void search();
      void del();
      void Del_Recolor(node *);
      node* successor(node *);
};

void RBtree::Insert()
{
     int z,i=0;
     int rno;
     string name1;
     cout<<"\nEnter Name : ";cin>>name1;
     cout<<"\nEnter RNo  :";cin>>rno;
     cout<<"\nEnter marks : "; cin>>z;
     node *p,*q;
     node *t=new node;
     t->name=name1;
     t->roll_no=rno;
     t->marks=z;
     t->class_rank=0;
     t->left=NULL;
     t->right=NULL;
     t->color='r';
     p=root;
     q=NULL;
     if(root==NULL)
     {
           root=t;
           t->parent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->marks<t->marks)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->marks<t->marks)
              q->right=t;
         else
              q->left=t;
     }

     Recolor(t);
     c++;
     cout << "\nC: " << c;
}
void RBtree::Recolor(node *t)
{
     node *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           node *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}

void RBtree::leftrotate(node *p)
{
     if(p->right==NULL)
           return ;
     else
     {
           node *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBtree::rightrotate(node *p)
{
     if(p->left==NULL)
          return ;
     else
     {
         node *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

void RBtree::FindRank()
{
    Inorder(root);
}
void RBtree::Inorder(node* n)
{
    if(n==NULL)
        return;
    Inorder(n->left);
    n->class_rank=c--;
    cout << "\nC: " << c;
    rno_node[n->roll_no]=n;
    Inorder(n->right);
}
void RBtree::display1()
{
    displayInorder1(root);
}
void RBtree::displayInorder1(node* n)
{
    if(n==NULL)
        return;
    displayInorder1(n->right);
    cout<<"\nName     : "<<n->name;
    cout<<"\nRoll No. : "<<n->roll_no;
    cout<<"\nMarks    : "<<n->marks;
    cout<<"\nRank     : "<<n->class_rank;
    cout<<endl;
    displayInorder1(n->left);
}
void RBtree::display2()
{
    cout<<"\nName\t\tRollNo.\t\tMarks\t\tRank\t\n";
    displayInorder2(root);
}
void RBtree::displayInorder2(node* n)
{
    if(n==NULL)
        return;
    displayInorder2(n->right);
    cout<<n->name<<"\t\t "<<n->roll_no<<"\t\t"<<n->marks<<"\t\t "<<n->class_rank<<"\n";
    displayInorder2(n->left);
}
void RBtree::displayRank()
{

     if(root==NULL)
     {
           cout<<"\nEmpty Tree\n" ;
           return ;
     }
     int rno;
     cout<<"\nEnter your Roll Number : "; cin>>rno;
     int mark=rno_node[rno]->marks;
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->roll_no==rno)
            {
                found=1;
            }
            if(found==0)
            {
                 if(p->marks<mark)
                    p=p->right;
                 else
                    p=p->left;
            }
     }
     if(found==0)
          cout<<"\nNot Found."<<endl;
     else
     {
        cout<<"The rank of selected student is "<<p->class_rank<<endl;
     }
}

void RBtree::del()
{
     if(root == NULL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }

     int x;

     cout<<"\nEnter the data of the node to be deleted: ";
     cin>>x;

     node *p;
     p=root;

     node *y=NULL;
     //0node *q=NULL;

     int found=0;

     while((p != NULL) && (found==0))
     {
        if(p->roll_no == x)
        {
            found = 1;
        }

        if(found==0)
        {
            if(p->roll_no  < x)
            {
                p=p->right;
            }

            else
            {
                p=p->left;
            }
        }
     }

     if(found==0)
     {
            cout<<"\nElement Not Found!";
            return ;
     }

     else
     {
         cout<<"\nDeleted Element: " << p->roll_no;
         cout<<"\nColour: ";

        if(p->color=='b')
        {
            cout<<"Black\n";
        }

        else
        {
            cout<<"Red\n";
        }

        if(p->parent!=NULL)
               cout<<"\nParent: "<<p->parent->roll_no;

        else
               cout<<"\nThere is no parent of the node. ";


        if(p->right!=NULL)
               cout<<"\nRight Child: "<<p->right->roll_no;

        else
               cout<<"\nThere is no right child of the node. ";

        if(p->left!=NULL)
               cout<<"\nLeft Child: "<<p->left->roll_no;

        else
               cout<<"\nThere is no left child of the node.  ";

         cout<<"\nNode Deleted.";

         if(p->left == NULL||p->right == NULL)
            y = p;

        else
            y = successor(p);

        if(y->left != NULL)
              q = y->left;

         else
         {
              if(y->right != NULL)
                   q = y->right;

              else
                   q = NULL;
         }
         if(q != NULL)
              q->parent = y->parent;

         if(y->parent == NULL)
              root=q;

         else
         {
             if(y == y->parent->left)
                y->parent->left=q;

             else
                y->parent->right=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->roll_no=y->roll_no;
         }
         if(y->color == 'b')
             Del_Recolor(q);
     }
}

void RBtree::Del_Recolor(node *p)
{
    node *s;
    while(p!=root&&p->color=='b')
    {
          if(p->parent->left==p)
          {
                  s=p->parent->right;

                  if(s->color=='r')
                  {
                         s->color='b';
                         p->parent->color='r';
                         leftrotate(p->parent);
                         s=p->parent->right;
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->color='r';
                             rightrotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftrotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightrotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftrotate(s);
                              s=p->parent->left;
                        }

                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightrotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}

node* RBtree::successor(node *p)
{
      node *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}



int main()
{
    int choice;

    bool loop = true;

    RBtree stud_rec;

    while (loop)
    {
                cout<<"\nRED BLACK TREE - STUDENT RECORD.\n" ;
                cout<<"\n1. Add new record.";
                cout<<"\n2. Calculate Rank.";
                cout<<"\n3. Rank of a record.";
                cout<<"\n4. Display - Record-wise.";
                cout<<"\n5. Display - Table.";
                cout << "\n6. Delete Record.";
                cout<<"\n7. Exit." ;
                cout<<"\nEnter Your Choice : ";
                cin>>choice;


                if (choice == 1)
                {
                    stud_rec.Insert();
                    cout<<"\nRecorded.\n";

                }

                else if (choice == 2)
                {
                    stud_rec.FindRank();
                    cout<<"\nRank Calculated.\n";
                }

                else if (choice == 3)
                {
                    stud_rec.displayRank();
                }

                else if (choice == 4)
                {
                    stud_rec.display1();
                }

                else if (choice == 5)
                {
                    stud_rec.display2();
                }

                else if (choice == 6)
                {
                    stud_rec.del();
                }

                else if (choice == 7)
                {
                    loop = false;
                }

                cout<<endl;
    }

    return 1;
}
