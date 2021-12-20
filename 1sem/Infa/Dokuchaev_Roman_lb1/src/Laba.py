import wikipedia

def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def is_language_valid(lang):
    if lang in wikipedia.languages():
        return lang
    else:
        print('no results')
        exit()

def max_words_summary(pages):
    maxi = 0
    maxi_page = None
    for i in pages:
        page = wikipedia.page(i)
        words = page.summary.split()
        if len(words) >= maxi:
            maxi = len(words)
            maxi_page = page.title
    return maxi, maxi_page

def find(page_1, page_2):
    for i in page_1.links:
        if not is_page_valid(i):
            continue
        page_i = wikipedia.page(i)
        if page_2.title == page_i.title:
            return None
        if page_2.title in page_i.links:
            return i
    return "ERROR"

def list_page(pages):
    b = 0
    while b < len(pages) - 1:
        c = find(wikipedia.page(pages[b]), wikipedia.page(pages[b + 1]))
        if c is not None:
            pages.insert(b + 1, c)
            b += 1
        b += 1
    return pages

a = input().split(', ')
lang = a[-1]
wikipedia.set_lang(is_language_valid(lang))

result = max_words_summary(a[0:len(a) - 1])
print(result[0], result[1])
print(list_page(a[0:len(a) - 1]))