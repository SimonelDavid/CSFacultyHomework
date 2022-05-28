using System;

namespace Proiect_SDA_mhir1707.TAD
{
    public class BSTNode<TElement> where TElement : IComparable<TElement>
    {
        public BSTNode<TElement> Parent { get; set; }

        public BSTNode<TElement> ChildLeft { get; set; }

        public BSTNode<TElement> ChildRight { get; set; }

        public TElement Element { get; set; }

        public BSTNode(TElement elem)
        {
            Parent = null;
            ChildLeft = null;
            ChildRight = null;
            Element = elem;
        }
    }

    public class OrderedList<TElement> where TElement : IComparable<TElement>
    {
        internal BSTNode<TElement> root;
        protected int count;

        public int Count
        {
            get
            {
                return count;
            }
        }

        public bool IsEmpty
        {
            get
            {
                return (root == null);
            }
        }

        public OrderedList()
        {
            root = null;
            count = 0;
        }

        public void Insert(TElement el)
        {
            BSTNode<TElement> node = new BSTNode<TElement>(el);

            if (root == null)
                root = node;
            else
                InsertNode(root, node);

            count += 1;
        }

        private void InsertNode(BSTNode<TElement> parent, BSTNode<TElement> node)
        {
            if (node.Element.CompareTo(parent.Element) < 0)
            {
                if (parent.ChildLeft == null)
                {
                    parent.ChildLeft = node;
                    node.Parent = parent;
                }
                else
                    InsertNode(parent.ChildLeft, node);
            }
            else if (node.Element.CompareTo(parent.Element) > 0)
            {
                if (parent.ChildRight == null)
                {
                    parent.ChildRight = node;
                    node.Parent = parent;
                }
                else
                    InsertNode(parent.ChildRight, node);
            }
        }

        public virtual void Remove(TElement el)
        {
            BSTNode<TElement> node = SearchElement_Rec(el, root);

            // Has no children
            if (node.ChildLeft == null && node.ChildRight == null)
            {
                if (node.Parent != null)
                {
                    if (node.Parent.ChildLeft == node)
                        node.Parent.ChildLeft = null;
                    else
                        node.Parent.ChildRight = null;
                }
                node = null;
                count -= 1;
            }
            // Has one child (Left)
            else if (node.ChildRight == null)
            {
                if (node.Parent != null)
                {
                    if (node.Parent.ChildLeft == node)
                    {
                        node.ChildLeft.Parent = node.Parent;
                        node.Parent.ChildLeft = node.ChildLeft;
                    }
                    else
                    {
                        node.ChildLeft.Parent = node.Parent;
                        node.Parent.ChildRight = node.ChildLeft;
                    }
                }
                node = null;
                count -= 1;
            }
            // Has one child (Right)
            else if (node.ChildLeft == null)
            {
                if (node.Parent != null)
                {
                    if (node.Parent.ChildRight == node)
                    {
                        node.ChildRight.Parent = node.Parent;
                        node.Parent.ChildRight = node.ChildRight;
                    }
                    else
                    {
                        node.ChildRight.Parent = node.Parent;
                        node.Parent.ChildLeft = node.ChildRight;
                    }
                }
                node = null;
                count -= 1;
            }
            // Has both children
            else
            {
                BSTNode<TElement> x = node;

                while (x.ChildLeft != null)
                    x = x.ChildLeft;

                node.Element = x.Element;
                BSTNode<TElement> nodeChild = x.ChildLeft == null ? x.ChildRight : x.ChildLeft;
                if (x.ChildLeft != null)
                {
                    if (x.Parent.ChildLeft == x)
                        x.Parent.ChildLeft = nodeChild;
                    else
                        x.Parent.ChildRight = nodeChild;
                }
                else
                {
                    if (x.Parent.ChildLeft == x)
                        x.Parent.ChildLeft = nodeChild;
                    else
                        x.Parent.ChildRight = nodeChild;
                }
                count -= 1;
            }
        }

        private BSTNode<TElement> SearchElement_Rec(TElement el, BSTNode<TElement> root)
        {
            BSTNode<TElement> node = root;

            if (node == null)
                return null;

            if (el.CompareTo(node.Element) == 0)
                return node;
            else if (el.CompareTo(node.Element) < 0)
                return SearchElement_Rec(el, node.ChildLeft);
            else
                return SearchElement_Rec(el, node.ChildRight);                       
        }

        public virtual void Clear()
        {
            root = null;
            count = 0;
        }

        public bool Contains(TElement el)
        {
            if (SearchElement_Rec(el, root) != null)
                return true;
            return false;
        }

        public Iterator<TElement> CreateIterator()
        {
            return new Iterator<TElement>(root);
        }
    }
}
