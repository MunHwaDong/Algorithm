using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyLinkedListIter<T> : IEnumerator<T>
{
    private Node<T> _head;
    private Node<T> current;

    public MyLinkedListIter(Node<T> head)
    {
        _head = head;
        current = null;
    }
    
    public bool MoveNext()
    {
        if (current == null)
        {
            current = _head;
        }
        else
        {
            current = current.Next;
        }

        return current != null;
    }

    public void Reset()
    {
        current = null;
    }

    public T Current
    {
        get
        {
            if (current == null) throw new InvalidOperationException();
            return current.Data;
        }
    }

    object IEnumerator.Current => Current;

    public void Dispose()
    {
    }
}
