using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node<T>
{
    public T Data { get; set; }
    public Node<T> Next { get; set; }
    public Node<T> Previous { get; set; }
    
    public Node(T data)
    {
        Data = data;
        Next = null;
        Previous = null;
    }

    public Node(T data, Node<T> next, Node<T> previous)
    {
        Data = data;
        Next = next;
        Previous = previous;
    }
}

public class MyLinkedList<T> : IEnumerable<T>
{
    public Node<T> Head { get; private set; }
    public Node<T> Tail { get; private set; }
    
    public uint Count { get; private set; }

    public void Add(T data)
    {
        Node<T> newNode = new Node<T>(data);

        if (Head == null)
        {
            Head = newNode;
        }
        else
        {
            Node<T> cur = Head;

            while (cur.Next != null) cur = cur.Next;

            cur.Next = newNode;
            newNode.Previous = cur;
        }

        Tail = newNode;
        Count++;
    }

    public void AddFirst(T data)
    {
        Node<T> newNode = new Node<T>(data);

        if (Head == null)
        {
            Head = newNode;
            Tail = newNode;
        }
        else
        {
            newNode.Next = Head;
            Head.Previous = newNode;
            Head = newNode;
        }
        Count++;
    }

    public void AddLast(T data)
    {
        Node<T> newNode = new Node<T>(data);

        if (Head == null)
        {
            Head = newNode;
            Tail = newNode;
        }
        else
        {
            Tail.Next = newNode;
            newNode.Previous = Tail;
            Tail = newNode;
        }
        Count++;
    }
    
    //Index version
    public void Remove(int idx)
    {
        int curIdx = 0;

        if (idx < 0) return;
        
        if (Head == null || idx < 0) return;
        else
        {
            Node<T> cur = Head;

            while (curIdx != idx)
            {
                cur = cur.Next;
                curIdx++;
            }
            
            //삭제할 노드를 찾지 못함
            if (curIdx >= Count) return;
            else if (Count == 1)
            {
                //한개만 있을땐 노드의 앞뒤가 null을 가르킬테니깐 null로 바꿔줄 필요 x
                Head = null;
                Tail = null;
                Count--;
            }
            else
            {
                if (curIdx == 0)
                {
                    Head = cur.Next;
                }
                else if (curIdx == Count - 1)
                {
                    cur.Previous.Next = null;
                    Tail = cur.Previous;
                }
                else
                {
                    cur.Previous.Next = cur.Next;
                    cur.Next.Previous = cur.Previous;
                }

                cur = null;
                Count--;
            }
        }
    }

    public void Traverse()
    {
        Node<T> current = Head;

        while (current != null)
        {
            Debug.Log(current.Data);
            current = current.Next;
        }
    }
    
    public void RTraverse()
    {
        Node<T> current = Tail;

        while (current != null)
        {
            Debug.Log(current.Data);
            current = current.Previous;
        }
    }

    public IEnumerator<T> GetEnumerator()
    {
        return new MyLinkedListIter<T>(Head);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
}
