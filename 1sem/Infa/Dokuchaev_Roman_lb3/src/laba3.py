class HouseScheme:
    def __init__(self, rooms, area, bathroom):
        self.rooms = rooms
        self.area = area
        self.bathroom = bathroom
        if not isinstance(self.rooms, int) or not isinstance(self.area, int) or not isinstance(self.bathroom, bool) or self.area <= 0:
            raise ValueError('Invalid value')


class CountryHouse(HouseScheme):
    def __init__(self, rooms, area, bathroom, floors, plot_area):
        super().__init__(rooms, area, bathroom)
        self.floors = floors
        self.plot_area = plot_area
        if not isinstance(self.floors, int) or not isinstance(self.plot_area, int):
            raise ValueError('Invalid value')


    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(self.rooms, self.area, self.bathroom, self.floors, self.plot_area)


    def __eq__(self, other):
        return self.area == other.area and self.plot_area == other.plot_area and abs(self.floors - other.floors) <= 1


class Apartment(HouseScheme):
    def __init__(self, rooms, area, bathroom, big_floors, windows):
        super().__init__(rooms, area, bathroom)
        if isinstance(big_floors, int) and windows in ['N', 'W', 'S', 'E'] and big_floors in range(1, 16):
            self.big_floors = big_floors
            self.windows = windows
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(
            self.rooms, self.area, self.bathroom, self.big_floors, self.windows)


class CountryHouseList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, CountryHouse):
            super().append(p_object)
        else:
            raise TypeError('Invalid type {}'.format(type(p_object)))

    def total_square(self):
        return sum([i.area for i in self])


class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for element in iterable:
            if isinstance(element, Apartment):
                self.append(element)

    def floor_view(self, big_floors, directions):
        filter_function = lambda obj: obj.big_floors in range(big_floors[0], big_floors[1] + 1) and obj.windows in directions
        result = list(filter(filter_function, self))
        for element in result:
            print('{}: {}'.format(element.windows, element.big_floors))