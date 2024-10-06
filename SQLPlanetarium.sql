CREATE TABLE Planets (
    ID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(50),
    DistanceFromEarth FLOAT,
    Diameter FLOAT,
    Type NVARCHAR(50),
    DiscoveryYear INT
);
