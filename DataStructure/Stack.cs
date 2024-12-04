using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StackNode<T>
{
    public T Data { get; set; }
    public StackNode<T> Previous { get; set; }
    
    public StackNode()
    {
        Data = default(T);
        Previous = null;
    }
    public StackNode(T data)
    {
        Data = data;
        Previous = null;
    }
}

public class MyStack<T> where T : new()
{
    public StackNode<T> Top { get; set; }
    public uint Count { get; private set; }

    public void Push(T data)
    {
        StackNode<T> node = new StackNode<T>(data);

        node.Previous = Top;
        Top = node;
        Count++;
    }

    public T Pop()
    {
        if (Top == null) return new T();
        else
        {
            T data = Top.Data;

            Top = Top.Previous;

            Count--;

            return data;
        }
    }

    public T Peek()
    {
        if (Top == null) return new T();
        
        else return Top.Data;
    }

    public bool IsEmpty()
    {
        return Top == null;
    }
}
