// ps 21

#include <iostream>
using namespace std;

class Heap
{
private:
    int size;
    int arr[100];

public:
    Heap()
    {
        size = 0;
        arr[0]=-1;
    }
    void swap(int &n1, int &n2)
    {
        int temp = n1;
        n1 = n2;
        n2 = temp;
    }
    void Insert(int val)
    {
        size += 1;
        int index = size;
        arr[index] = val;
        while (index > 1)
        {
            int parent = index / 2;
            if (arr[parent] < arr[index])
            {
                swap(arr[parent], arr[index]);
                index=parent;
            }
            else
            {
                return;
            }
        }
    }
    void print()
    {
        for (int i = 1; i <= size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void Heapify(int arr[], int n, int i)
    {
        int largest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (arr[largest] < arr[left] && left < n)
        {
            largest = left;
        }
        if (arr[largest] < arr[right] && right < n)
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            Heapify(arr, n, largest);
        }
    }

    void HeapSort()
    {
        int n = size;
        while (n > 1)
        {
            swap(arr[n], arr[1]);
            n--;
            Heapify(arr, n , 1);
        }
    }
};
int main()
{
    Heap h;
    int choice;
    int n, data;

    cout << "how many elements u want to enter" << endl;
    cin >> n;
    while (n--)
    {
        cout << "enter data" << endl;
        cin >> data;
        h.Insert(data);
    }

    while (true)
    {

        cout << "2->display heap" << endl;
        cout << "3->sort heap" << endl;

        cin >> choice;

        if (choice == 2)
        {
            h.print();
        }
        if (choice == 3)
        {
            h.HeapSort();
        }
    }

    return 0;
}