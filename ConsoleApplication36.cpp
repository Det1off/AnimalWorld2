#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Herbivore {
protected:
    int weight;
    bool life;

public:
    Herbivore(int weight) : weight(weight), life(true) {}

    virtual void EatGrass() {
        if (life) {
            weight += 10;
            cout << "Травоядное кушает траву. Вес теперь: " << weight << endl;
        }
        else {
            cout << "Это животное мертво и не может есть траву." << endl;
        }
    }

    int GetWeight() const { return weight; }
    bool IsAlive() const { return life; }
    void Kill() { life = false; }

    virtual string GetName() const = 0;
    virtual ~Herbivore() {}
};

class Carnivore {
protected:
    int power;

public:
    Carnivore(int power) : power(power) {}

    virtual void Eat(Herbivore* herbivore) {
        if (!herbivore->IsAlive()) {
            cout << herbivore->GetName() << " уже мертва. Хищник не может её съесть." << endl;
            return;
        }

        if (power > herbivore->GetWeight()) {
            power += 10;
            herbivore->Kill();
            cout << GetName() << " съел " << herbivore->GetName()
                << ". Сила теперь: " << power << endl;
        }
        else {
            power -= 10;
            cout << GetName() << " не смог победить " << herbivore->GetName()
                << ". Сила уменьшилась: " << power << endl;
        }
    }

    int GetPower() const { return power; }

    virtual string GetName() const = 0;
    virtual ~Carnivore() {}
};

class MythicalAnimal : public Herbivore, public Carnivore {
private:
    string name;

public:
    MythicalAnimal(string name, int weight, int power)
        : Herbivore(weight), Carnivore(power), name(name) {
    }

    void EatGrass() override {
        if (life) {
            weight += 15;
            cout << name << " (мифическое животное) ест траву. Вес теперь: " << weight << endl;
        }
        else {
            cout << name << " мертво и не может есть траву." << endl;
        }
    }

    void Eat(Herbivore* herbivore) override {
        if (!herbivore->IsAlive()) {
            cout << herbivore->GetName() << " уже мертва. " << name << " не может её съесть." << endl;
            return;
        }

        if (power > herbivore->GetWeight()) {
            power += 15;
            herbivore->Kill();
            cout << name << " (мифическое животное) съел " << herbivore->GetName()
                << ". Сила теперь: " << power << endl;
        }
        else {
            power -= 15;
            cout << name << " не смог победить " << herbivore->GetName()
                << ". Сила уменьшилась: " << power << endl;
        }
    }

    string GetName() const override { return name; }
};

class Africa {
public:
    Herbivore* CreateHerbivore() {
        return new Herbivore(50);
    }

    Carnivore* CreateCarnivore() {
        return new Carnivore(100);
    }
};

int main() {
    cout << "Тестирование мифического животного:\n";

    MythicalAnimal griffin("Грифон", 60, 80);

    cout << "Вес: " << griffin.GetWeight() << ", Сила: " << griffin.GetPower() << endl;

    Herbivore* wildebeest = new Herbivore(40);

    griffin.EatGrass();
    griffin.Eat(wildebeest);

    delete wildebeest;

    return 0;
}
