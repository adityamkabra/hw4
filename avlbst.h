#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    void insertfix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void rightright(AVLNode<Key,Value>* n);
    void leftleft(AVLNode<Key,Value>* n);
    int balencee(AVLNode<Key,Value>* n);
    int heightt(AVLNode<Key, Value>* root) const;
    void removeFix(AVLNode<Key,Value>* n, int difference);

    // Add helper functtions here


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
       AVLNode<Key,Value>* n=new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);

    if(this->root_==nullptr)
    {
      this->root_=n;
      return;
    }
    AVLNode<Key,Value>* ctr = static_cast<AVLNode<Key,Value>*>(this->root_);
    while(true)
    {
      if(new_item.first<ctr->getKey())
      {
        if(ctr->getLeft()==nullptr)
        {
          int balence = ctr->getBalance();
          ctr->setLeft(n);
          n->setParent(ctr);
          ctr->updateBalance(1);
          n->setBalance(0);
          if(balence==0)
          {
            insertfix(ctr,n);
          }
         
          return;


        }
        ctr=ctr->getLeft();
        
        
      }
      else if(new_item.first>ctr->getKey())
      {
        if(ctr->getRight()==nullptr)
        {
          int balence = ctr->getBalance();
          ctr->setRight(n);
          n->setParent(ctr);
          ctr->updateBalance(-1);
          n->setBalance(0);
          
          if(balence==0)
          {
            insertfix(ctr,n);
          }
          
      

          return;
        }
        ctr=ctr->getRight();

      }
      else
      {

        ctr->setValue(n->getValue());
        delete n;
        return;
        
      }

    }



    
    

    
}


template<class Key, class Value>
void AVLTree<Key, Value>::insertfix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
  if(p==nullptr||p->getParent()==nullptr)
  {
    
    return;
  }
  
  AVLNode<Key,Value>* g = nullptr;
  
  g=p->getParent();

  

  int new_balence = 0;
  if(g->getLeft()==p)
  {
    g->updateBalance(1);
  }
  else
  {
    g->updateBalance(-1);
  }
  new_balence=g->getBalance();
  
  if(new_balence==0)
  {
    return;
  }
  if(new_balence==1||new_balence==-1)
  {
    insertfix(g,p);
    
  }
  if(new_balence==2||new_balence==-2)
  {
    if(new_balence==2)
    {
      if(p->getBalance()==1)
      {
        leftleft(p);
        p->setBalance(0);
        g->setBalance(0);
      }
      else if(p->getBalance()==-1)
      {
        rightright(n);
        leftleft(n);
        if(n->getBalance()==0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else if(n->getBalance()==1)
        {
           p->setBalance(0);
           g->setBalance(-1);
           n->setBalance(0);

        }
        else
        {
           p->setBalance(1);
           g->setBalance(0);
           n->setBalance(0);

        }
        
      }
    }
    else
    {
      if(p->getBalance()==-1)
      {
        rightright(p);
        p->setBalance(0);
        g->setBalance(0);
        
      }
      else if(p->getBalance()==1)
      {
        
        leftleft(n);
        
        
        rightright(n);
        if(n->getBalance()==0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else if(n->getBalance()==-1)
        {
           p->setBalance(0);
           g->setBalance(1);
           n->setBalance(0);

        }
        else
        {
            p->setBalance(-1);
            g->setBalance(0);
            n->setBalance(0);

        }
        
        
      }

    }

  }




  

}



template<class Key, class Value>
void AVLTree<Key, Value>::leftleft(AVLNode<Key,Value>* p)
{
  if(p==nullptr)
  {
    return;
  }
  AVLNode<Key,Value>* g = p->getParent();
  if(g==nullptr)
  {
    return;
  }
  AVLNode<Key,Value>* gg = g->getParent();
  if(gg!=nullptr)
  {
    if(gg->getLeft()==g)
    {
      gg->setLeft(p);
    }
    else
    {
      gg->setRight(p);
    }
  }
  else
  {
    this->root_=p;
  }
  g->setLeft(p->getRight());
  if(p->getRight()!=nullptr)
  {
    p->getRight()->setParent(g);
  }
  p->setRight(g);
  g->setParent(p);
  p->setParent(gg);
  



}

template<class Key, class Value>
void AVLTree<Key, Value>::rightright(AVLNode<Key,Value>* p)
{
  if(p==nullptr)
  {
    return;
  }
  AVLNode<Key,Value>* g = p->getParent();
  if(g==nullptr)
  {
    return;
  }
  AVLNode<Key,Value>* gg = g->getParent();
  if(gg!=nullptr)
  {
    if(gg->getRight()==g)
    {
      gg->setRight(p);
    }
    else
    {
      gg->setLeft(p);
    }
  }
  else
  {
    this->root_=p;
  }
  g->setRight(p->getLeft());
  if(p->getLeft()!=nullptr)
  {
    p->getLeft()->setParent(g);
  }
  p->setLeft(g);
  g->setParent(p);
  p->setParent(gg);
  



}

template<class Key, class Value>
int AVLTree<Key, Value>::balencee(AVLNode<Key,Value>* n)
{
  
  return (heightt(n->getLeft()))-(heightt(n->getRight()));
  


}
template<class Key, class Value>
int AVLTree<Key, Value>::heightt(AVLNode<Key, Value>* root)const
{
  if(root==nullptr)
  {
    return 0;
  }
  return 1+ max(heightt(root->getLeft()),heightt(root->getRight()));
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.

 */




template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
    while(temp!=nullptr)
    {
      if(temp->getKey()==key)
      {
        break;

      }
      else if(key<temp->getKey())
      {
        temp = temp->getLeft();
      }
      else
      {
        temp = temp->getRight();
      }

    }
    if(temp!=nullptr)
    {
      if(temp->getLeft()!=nullptr&&temp->getRight()!=nullptr)
      {
        AVLNode<Key, Value>* temp1 = static_cast<AVLNode<Key,Value>*>(this->predecessor(temp));
        nodeSwap(temp,temp1);
        
      }
      if(temp->getLeft()!=nullptr&&temp->getRight()==nullptr)
      {
        if(temp==this->root_)
        {
      
            this->root_=temp->getLeft();
            this->root_->setParent(nullptr);
            delete temp;
          
        }
        else
        {
          AVLNode<Key, Value>* parent = temp->getParent();
          AVLNode<Key, Value>* child = temp->getLeft();
          int difference =0;
          if(parent->getLeft()==temp)
          {
            (parent)->setLeft(child);
            difference=-1;
          }
          else
          {
            (parent)->setRight(child);
            difference =1;

          }
          //parent->updateBalance(difference);
          (child)->setParent(parent);

          delete temp;
          removeFix(parent,difference);
        }
         
      }
      else if(temp->getLeft()==nullptr&&temp->getRight()!=nullptr)
      {
         
            
        
          if(temp==this->root_)
          {
            this->root_=temp->getRight();
            this->root_->setParent(nullptr);
            delete temp;
          }
          else
          {
          
          
            AVLNode<Key, Value>* parent = temp->getParent();
            AVLNode<Key, Value>* child = temp->getRight();
            int difference =0;
            if(parent->getLeft()==temp)
            {
              (parent)->setLeft(child);
              difference = -1;
            }
            else
            {
              (parent)->setRight(child); 
              difference = 1;

            }
            //parent->updateBalance(difference);
            (child)->setParent(parent);
             delete temp;
             removeFix(parent,difference);
          }

      }
      else if(temp->getLeft()==nullptr&&temp->getRight()==nullptr)
      {
        if(temp==this->root_)
        {
          delete temp;
          this->root_=nullptr;
        }
        else
        {
          
            AVLNode<Key, Value>* parent = temp->getParent();
            int difference =0;
          
            if((parent)->getLeft()==temp)
            {
              (parent)->setLeft(nullptr);
              difference = -1;
              //parent->updateBalance(difference);
              delete temp;
            }
            else
            {
              (parent)->setRight(nullptr);
              difference =1;
              //parent->updateBalance(difference);
              delete temp;

            }  
            removeFix(parent,difference);
          
        }
      }      
    }
    else
    {
      return;
    }

}



template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key,Value>* n, int difference)
{
  if(n==nullptr)
  {
    return;
  }
  AVLNode<Key,Value>* p = n->getParent();
  int nextdiff = 0;
  if(p!=nullptr)
  {
    if(p->getLeft()==n)
    {
      nextdiff=-1;
    }
    else
    {
      nextdiff=1;
    }
  }
  if(n->getBalance()+difference==-2||n->getBalance()+difference==2)
  {

    if(n->getBalance()+difference==2)
    {
      AVLNode<Key, Value>* child = n->getLeft();
      AVLNode<Key, Value>* parent = n->getParent();
      if(child->getBalance()==1)
      {
        //AVLNode<Key,Value>* gchild = nullptr;
        
        
        leftleft(child);
        n->setBalance(0);
        (child)->setBalance(0);
        //gchild->setBalance(0);


        removeFix(parent,nextdiff);
      }
      else if(child->getBalance()==0)
      {
        
        
        leftleft(child);
        n->setBalance(1);
        (child)->setBalance(-1);
        


      }
      else if(child->getBalance()==-1)
      {
        //AVLNode<Key,Value>* child = n->getRight();
        AVLNode<Key,Value>* parent = n->getParent();
        AVLNode<Key,Value>* gchild = nullptr;
        gchild = child->getRight();
       
        rightright(gchild);
        leftleft(gchild);
        if(gchild->getBalance()==-1)
        {
          n->setBalance(0);
          child->setBalance(1);
          gchild->setBalance(0);

        }
        else if(gchild->getBalance()==1)
        {
          n->setBalance(-1);
          child->setBalance(0);
          gchild->setBalance(0);

        }
        else if(gchild->getBalance()==0)
        {
          n->setBalance(0);
          child->setBalance(0);
          gchild->setBalance(0);

          

        }
        removeFix(parent, nextdiff);
      }

    }
    if(n->getBalance()+difference==-2)
    {
      AVLNode<Key, Value>* child = n->getRight();
      if(child->getBalance()==-1)
      {
        AVLNode<Key,Value>* parent = n->getParent();
        rightright(child);
        n->setBalance(0);
        (child)->setBalance(0);
        //(n->getParent())->setBalance(0);
        
        removeFix(parent,nextdiff);
      }
      else if(child->getBalance()==0)
      {
       
        rightright(child);
        n->setBalance(-1);
        (child)->setBalance(1);
        


      }
      else if(child->getBalance()==1)
      {
        //AVLNode<Key,Value>* child = n->getRight();
        AVLNode<Key,Value>* parent = n->getParent();
        AVLNode<Key,Value>* gchild = nullptr;
       
        gchild = child->getLeft();

        
        leftleft(gchild);
        rightright(gchild);
        if(gchild->getBalance()==1)
        {
          n->setBalance(0);
          child->setBalance(-1);
          gchild->setBalance(0);

        }
        else if(gchild->getBalance()==-1)
        {
          n->setBalance(1);
          child->setBalance(0);
          gchild->setBalance(0);

        }
        else if(gchild->getBalance()==0)
        {
          n->setBalance(0);
          child->setBalance(0);
          gchild->setBalance(0);

          

        }
        removeFix(parent, nextdiff);
      }
    }

  }
  else if(n->getBalance()+difference==1)
  {
      n->setBalance(1);

  }
  else if(n->getBalance()+difference==-1)
  {
      n->setBalance(-1);

  }
  else if(n->getBalance()+difference==0)
  {
      n->setBalance(0);
      removeFix(n->getParent(), nextdiff);

  }





  

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
