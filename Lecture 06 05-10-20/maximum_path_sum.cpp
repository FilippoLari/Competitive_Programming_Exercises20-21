/*
    the algorithm traverse the tree in a post-order way.
    For each node it computes the maximum path sum 
    from it to the leafs of the left and right subtree.
    
    Once these values are computed it sums them up with the
    key of the node and compare this value with the maxium,
    updating it if necessary.

    The running time is O(n) and uses O(1) space.
*/

int aux(Node* root, int *max)
{
    if(root==NULL) return INT_MIN;
    
    int left = aux(root->left, max);
    int right = aux(root->right, max);
    
    //found a leaf
    if(left==INT_MIN && right==INT_MIN) return root->data;
    
    int path_sum = root->data;
    
    if(left>right) path_sum += left;
    else path_sum += right;
    
    if(left!=INT_MIN && right!=INT_MIN && left+right+root->data>*max)
        *max = left+right+root->data;
    
    return path_sum;
}

int maxPathSum(Node* root)
{ 
    int max = INT_MIN;
    aux(root, &max);
    return max;
}
