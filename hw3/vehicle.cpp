//Your declarations and implementations would go here
class Vehicle
{
    public:
        Vehicle(string id)
        {
            m_id = id;
        }
        virtual ~Vehicle()
        {}
        string id() const
        {
            return m_id;
        }
        virtual string description() const = 0;
        virtual bool canHover() const
        {
            return true;
        }
    private:
        string m_id;
};
class Drone : public Vehicle
{
    public:
        Drone(string id) : Vehicle(id)
        {}
        virtual ~Drone()
        {
            cout << "Destroying " << id() << ", a drone" << endl;
        }
        virtual string description() const
        {
            return "a drone";
        }
};
class Balloon : public Vehicle
{
    public:
        Balloon(string id, double diameter) : Vehicle(id)
        {
            m_diam = diameter;
        }
        string determineSize() const
        {
            if (m_diam < 8)
                return "small";
            return "large";
        }
        virtual ~Balloon()
        {
            cout << "Destroying the balloon " << id() << endl;
        }
        virtual string description() const
        {
            return "a " + determineSize() + " balloon";
        }
    private:
        double m_diam;
};
class Satellite : public Vehicle
{
    public:
        Satellite(string id) : Vehicle(id)
        {}
        virtual ~Satellite()
        {
            cout << "Destroying the satellite " << id() << endl;
        }
        virtual string description() const
        {
            return "a satellite";
        }
        virtual bool canHover() const
        {
            return false;
        }
};

