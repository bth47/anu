public class Main2 {
    public static void main(String[] args){
   
        SLinkedList<Integer> sl = new SLinkedList<Integer>();

        sl.insert( 40 );
        sl.insert( 20 );
        sl.insert( 60 );
        sl.insert( 10 );
        sl.insert( 30 );
        sl.insert( 50 );
        sl.insert( 70 );
        sl.show( );
       
    }
}


class SLinkedList<ET extends Comparable<ET>> implements LinearList<ET>
{
    private Node<ET> first; 
    private int size; 
    public SLinkedList( ) { first = null; } 

    class Node<ET> { 
        private ET elem;
        private Node next;
        
        Node( ET elem, Node next ) {
        this.elem= elem;
        this.next= next;
    } 
} 

    public void insert( ET theElem) {
        
        Node<ET> newNode = new Node<ET>(theElem, null);

        if (first == null || theElem.compareTo(first.elem) <= 0) {
            newNode.next = first;
            first = newNode;
        } else {
            Node<ET> cn = first;
            Node<ET> pn = null;

            while (cn != null && theElem.compareTo(cn.elem) > 0) {
                pn = cn;
                cn = cn.next;
            }

            newNode.next = cn;
            pn.next = newNode;
        }

        size++;
    }
    
    public boolean remove( ET theElem) {
        Node<ET> pn= null, cn= first;
        for( cn= first; cn!= null; cn= cn.next) { 
            if( cn.elem.equals(theElem) ) break;
            pn= cn;
        }

        if( cn == null ) return false; 
        
        pn.next= cn.next; 
        size--;
        return true;
    }

    public int search( ET theElem) { 
       int i= 0;
       for( Node<ET> cn= first; cn!= null; cn= cn.next ) {
            if( cn.elem.equals(theElem) ) return i;
            i++;
         }
        return -1;
    } 

    public ET get( int index ) { 
        if( index < 0 || index >= size ) 
            throw new IndexOutOfBoundsException("예외");

        Node<ET> cn= first;
        for( int i= 0; i < index; i++ ) {
            cn= cn.next;
        }
        return cn.elem;
    }

    void show(){ 
        Node<ET> cn = first;
        while (cn != null) {
            System.out.print(cn.elem + " ");
            cn = cn.next;
        }
        System.out.println();
    }
}

interface LinearList<ET> {
   
    void insert( ET e );
    boolean remove( ET e );
    int search( ET e );
    ET get( int index );
}