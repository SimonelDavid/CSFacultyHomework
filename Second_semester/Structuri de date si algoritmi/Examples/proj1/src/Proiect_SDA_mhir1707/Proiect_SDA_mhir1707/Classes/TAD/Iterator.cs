using System;
using System.Collections.Generic;

namespace Proiect_SDA_mhir1707.TAD
{
    public class Iterator<TElement> where TElement : IComparable<TElement>
    {
        private BSTNode<TElement> current;

        public TElement CurrentElement
        {
            get
            {
                return current.Element;
            }
        }

        public bool Valid
        {
            get
            {
                return current != null;
            }
        }

        public Iterator(BSTNode<TElement> root)
        {
            this.current = FindMinimum(root);
        }

        public void Next()
        {
            if (current.ChildRight != null)
            {
                current = FindMinimum(current.ChildRight);
                return;
            }

            BSTNode<TElement> y = current.Parent;
            BSTNode<TElement> x = current;

            while (y != null && x == y.ChildRight)
            {
                x = y;
                y = y.Parent;
            }

            current = y;
        }

        public void Previous()
        {
            if (current.ChildLeft != null)
            {
                current = FindMaximum(current.ChildLeft);
                return;
            }

            BSTNode<TElement> y = current.Parent;;
            BSTNode<TElement> x = current;

            while (y != null && x == y.ChildLeft)
            {
                x = y;
                y = y.Parent;
            }

            current = y;
        }

        private BSTNode<TElement> FindMinimum(BSTNode<TElement> root)
        {
            if (root == null)
                return null;

            if (root.ChildLeft != null)
                return FindMinimum(root.ChildLeft);

            return root;
        }

        private BSTNode<TElement> FindMaximum(BSTNode<TElement> root)
        {
            if (root == null)
                return null;

            if (root.ChildRight != null)
                return FindMaximum(root.ChildRight);

            return root;
        }
    }
}

