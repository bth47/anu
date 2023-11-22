public class hw1 {
    public static void main(String[] args){
   
        ArrayListSorted<Integer> al = new ArrayListSorted<Integer>();
        al.insert( 40 );
        al.insert( 50 );
        al.insert( 60 );
        al.insert( 10 );
        al.insert( 20 );
        al.insert( 30 );
        al.show( );
       
        int r = 0;
        r = al.search( 30 );
        System.out.println("반환값 r 출력: " + r);
        r = al.search( 90 );
        System.out.println("반환값 r 출력: " + r);
        r = al.binarySearch( 30 );
        System.out.println("반환값 r 출력: " + r);
        r = al.binarySearch( 90 );
        System.out.println("반환값 r 출력: " + r);
        int result = al.get(3);
        System.out.println("al.get(3)의 결과: " + result);
        al.remove( 30 );
        al.remove( 10 );
        al.remove( 60 );
        al.show( );
    }
}

class ArrayListSorted<ET> implements LinearList<ET> {
       
        ET elem[ ]; 
       
        int size; 
       
        static final int INIT_CAPACITY = 5; 
        public ArrayListSorted( ) { this( INIT_CAPACITY ); }
   
        public ArrayListSorted( int initCapacity ) {
       
        elem= (ET[ ]) new Object[initCapacity];
    }

    public void insert( ET theElem ) { 
       
        if( size == elem.length ) changeCapacity( 2*size );
       
        int i = 0;
       
        Comparable<ET> e = (Comparable<ET>) theElem;
       
        while( i < size && e.compareTo(elem[i]) > 0 ) i++; 
       
        for( int j = size; j > i; j-- ) { 
            elem[j] = elem[j-1];
        }
   
        elem[i] = theElem; 
       
        size++;
    }
   
    public boolean remove( ET theElem ) { 
       
        int i;
       
        for( i = 0; i < size; i++ ) 
            if( elem[i].equals(theElem) ) break;
       
        if( i == size ) return false; 
       
        for( ; i < size-1; i++ ) 
            elem[i] = elem[i+1];
       
        size--;
       
        if( size <= elem.length/4 ) changeCapacity( elem.length/2 );
       
        return true; 
    }

    protected void changeCapacity( int newCapacity ) { 
       
        ET[ ] tmp = (ET[ ]) new Object[newCapacity]; 

        for( int i = 0; i < size; i++ ) { 
            tmp[i] = elem[i];
        }
   
        elem = tmp; 
    }
   
    public int binarySearch( ET theElem ) { 
       
        Comparable<ET> e = (Comparable<ET>) theElem;
        int p = 0;
        int q = size - 1;

        while( p <= q ) {
            int m = (p + q) / 2;
            if( e.compareTo(elem[m]) == 0 ) {
                return m;
            }
            else if( e.compareTo(elem[m]) < 0 ) {
                q = m - 1;
            } else {
                p = m + 1;
            }
        }

        return -1;
    }
       
    public int search( ET theElem ) {
       
        int i;
       
        for( i = 0; i < size; i++ )
       
        if( elem[i].equals(theElem) ) return i;    
       
        return -1;
    }
   
    public ET get( int index ) { 
       
        if( index < 0 || index >= size ) 
            throw new ArrayIndexOutOfBoundsException("exception");

        return elem[index];
    }

    void show(){
       
       for (int i = 0; i < size; i++) {
            System.out.print(elem[i] + " ");
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