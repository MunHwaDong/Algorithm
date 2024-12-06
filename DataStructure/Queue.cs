namespace Q
{
    public class Node<T>
    {
        public T Data { get; set; }
        public Node<T> Next { get; set; }

        public Node(T data)
        {
            Data = data;
            Next = null;
        }
    }
    public class NodeQueue<T> : MonoBehaviour
    {
        private Node<T> front;
        private Node<T> rear;
        
        public uint Count { get; set; }

        public void Enqueue(T data)
        {
            Node<T> curNode = new Node<T>(data);
            
            if (front == null)
            {
                front = curNode;
                rear = curNode;
            }
            else
            {
                rear.Next = curNode;
                rear = curNode;
            }
            
            Count++;
        }

        public T Dequeue()
        {
            if (front == null) throw new System.Exception("Queue is empty");
            
            T returnData = front.Data;

            front = front.Next;
            Count--;

            if (front == null) rear = null;
            
            return returnData;
        }
    }
}
