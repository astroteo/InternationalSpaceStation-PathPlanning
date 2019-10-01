class Node // Difficult to create a map of nodes
{
  public:
    Node(pcl::PointXYZI p_) : up(nullptr),down(nullptr), left(nullptr),right(nullptr)
  {
    this->p.push_back(p_.x);
    this->p.push_back( p_.y);
    this->p.push_back( p_.z);
    this->free = p_.intensity > 0 ? true : false;

  }

  ~Node(){}


  public:
    ptype p;
    bool free;
    Node *up, *down, *left, *right;
    bool is_goal = false;

  };
