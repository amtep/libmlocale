/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef MLOCALE_H
#define MLOCALE_H

#include "mexport.h"

#include <QtGlobal>
#include <QObject>

class QString;
class QStringList;
class QDateTime;

class MCollator;
class MAbstractName;
class MCalendar;
class MBreakIteratorPrivate;

class MLocalePrivate;

/*!
 * \class MLocale
 *
 * \brief MLocale is a class that implements locale dependent data formatting as well as translation, collation and calendar systems.
 *
 * For more general information about Internationalization in libmeegotouch
 * see also the <a href="i18n.html">Internationalization Guidelines</a>
 *
 * The locale system in the MeeGo Touch UI Framework is separated into
 * different categories. These correspond roughly to the LC_*
 * environment variables of POSIX. MLocale is created with one main
 * language setting but category settings can be used to override
 * specific details.  For example it is possible to set the main
 * language to “en_US” to get user interface messages in English but
 * set the MLcCollate category to “fi_FI” to get Finnish collation and
 * set the MLcNumeric category to “de_DE” to get German number
 * formatting.
 *
 * The calendar system in the MeeGo Touch UI Framework supports a
 * number of non-Gregorian calendar systems. The calendar is used to
 * create presentations of date and time.
 *
 * The collation system in the MeeGo Touch UI Framework supports a
 * number of collation systems. The actual collation is done with the
 * MCollator class.
 *
 * The translation system in the MeeGo Touch UI Framework differs a
 * bit from the usual practice used in any other translation system
 * (e.g, Qt’s tr() or GNU’s gettext). In the MeeGo Touch UI Framework,
 * a developer has to use both logical names and Engineering English
 * to translate a string.  Whenever no translation is available, the
 * Engineering English version, which is auto-generated from the
 * source code, is displayed instead of the logical names to make
 * testing easier.  The displayed Engineering English is prefixed with
 * “!! ” to make it obvious that no translation was found and a proper
 * translation still needs to be added.  Internally, the MeeGo
 * Touch UI Framework translation system uses the Qt translation
 * system (using the QTranslator class). The translation source file
 * is in .ts format version 3.0. Usually the translation source file
 * is not generated from code, but rather generated by some other
 * means (e.g from the UI specification).
 *
 * If one wants to react when the locale settings are changed, one can
 * connect to the settingsChanged() signal by using the
 * connectSettings() method.
 *
 * \note The methods are not thread-safe. For number/string formatting etc. the class is re-entrant. If one needs to have formatting in multiple threads it is suggested to create separate locales.
 */


class M_EXPORT MLocale : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief enum for Date formatting.
     *
     * This correlates closely with the <a
     * href="http://userguide.icu-project.org/formatparse/datetime#TOC-Producing-Normal-Date-Formats-for-a">
     * date type in ICU</a> and Unicode CLDR
     */
    enum DateType {
        DateNone,
        DateShort,
        DateMedium,
        DateLong,
        DateFull
    };

    /*!
     * \brief enum for Time formatting.
     *
     * This correlates closely with the <a
     * href="http://userguide.icu-project.org/formatparse/datetime#TOC-Producing-Normal-Date-Formats-for-a">
     * time type in ICU</a> and Unicode CLDR
     */
    enum TimeType {
        TimeNone,
        TimeShort,
        TimeMedium,
        TimeLong,
        TimeFull
    };

    // NOTE: could add LC_CTYPE, LC_PAPER, LC_ADDRESS, LC_TELEPHONE,
    // LC_MEASUREMENT, LC_IDENTIFICATION?

    //! Category type for the locale
    enum Category {MLcMessages, MLcTime, MLcCollate,
                   MLcNumeric, MLcMonetary, MLcName
                  };

    //! Set of possible collations
    enum Collation {DefaultCollation, PhonebookCollation, PinyinCollation,
                    TraditionalCollation, StrokeCollation, DirectCollation,
                    PosixCollation, Big5hanCollation, Gb2312hanCollation
                   };

    //! Calendar type.
    enum CalendarType {DefaultCalendar, GregorianCalendar, IslamicCalendar,
                       ChineseCalendar, IslamicCivilCalendar, HebrewCalendar,
                       JapaneseCalendar, BuddhistCalendar, PersianCalendar,
                       CopticCalendar, EthiopicCalendar
                      };

    enum Weekday {Monday = 1, Tuesday, Wednesday, Thursday, Friday,
                  Saturday, Sunday
                 };


    //! Return type for MCollator::compare(). Denotes the order of two strings.
    enum Comparison {LessThan = -1, Equal = 0, GreaterThan = 1};


    //! Type for locale dependant date symbol presentation
    enum DateSymbolContext {DateSymbolFormat, DateSymbolStandalone};

    //! Length type for date symbol presentation
    enum DateSymbolLength {DateSymbolAbbreviated, DateSymbolWide, DateSymbolNarrow};


    /*!
     * \ brief Grouping formats for phone numbers
     * The phone number grouping specifies, how phone numbers will
     * be displayed to the user.
     * NoGrouping means that the phone numbers are not grouped at all.
     * NorthAmericanGrouping means that the phone numbers are grouped
     * according to the "North American Numbering Plan"
     * DefaultGrouping means that grouping is done according to the
     * current system settings.
     */
    enum PhoneNumberGrouping {
      DefaultGrouping,
      NoGrouping,
      NorthAmericanGrouping
    };


    static MLocale *createSystemMLocale();
    static MLocale createCLocale();

    /*!
     * \brief Constructs a MLocale as a copy of the current system default locale
     * \param parent the Object’s parent
     *
     * If MLocale is instantiated with this constructor, i.e.  without
     * the parameter specifying the locale name in ICU format as in the other
     * constructor
     * MLocale(const QString &localeName, QObject *parent), it will
     * return a copy of the system default locale, if this already
     * exists. If the system default locale does not exist yet, it is
     * created based on the global settings in the relevant gconf
     * keys. If the gconf settings are not available the system
     * default locale is created based on the contents of the LANG
     * environment variable.
     *
     * The copy of the system default locale created may already have a list
     * of translation catalogs installed, more translation catalogs
     * can be added using installTrCatalog().
     *
     * \sa MLocale(const QString &localeName, QObject *parent)
     * \sa installTrCatalog(const QString &name)
     * \sa setDefault(const MLocale &locale)
     *
     */
    explicit MLocale(QObject *parent = 0);

    /*!
     * \brief Constructs a MLocale from a ICU format locale ID string
     * \param localeName ICU format locale ID string.
     * \param parent the Object’s parent
     *
     * For details about ICU format locale ID strings
     * see http://userguide.icu-project.org/locale .
     *
     * <table border="1">
     * <caption>
     *   <big><b>
     *     Examples for ICU format locale ID strings
     *   </b></big>
     * </caption>
     * <tr>
     *   <th>Locale ID</th>
     *   <th>Language</th>
     *   <th>Script</th>
     *   <th>Country</th>
     *   <th>Variant</th>
     *   <th>Keywords</th>
     *   <th>Comment</th>
     * </tr>
     * <tr>
     *   <td>fi_FI</td>
     *   <td>fi</td>
     *   <td></td>
     *   <td>FI</td>
     *   <td></td>
     *   <td></td>
     *   <td>Finnish language in Finland, default sorting order</td>
     * <tr>
     *   <td>fi_FI@collation=phonebook</td>
     *   <td>fi</td>
     *   <td></td>
     *   <td>FI</td>
     *   <td></td>
     *   <td>collation=phonebook</td>
     *   <td>Finnish language in Finland, phonebook sorting order</td>
     * </tr>
     * <tr>
     *   <td>zh_CN@collation=stroke;calendar=chinese</td>
     *   <td>zh</td>
     *   <td></td>
     *   <td>CN</td>
     *   <td></td>
     *   <td>collation=stroke;calendar=chinese</td>
     *   <td>Simplified Chinese with sorting via stroke-count and Chinese calendar</td>
     * </tr>
     * </tr>
     * </table>
     *
     * \sa MLocale(QObject *parent)
     */
    explicit MLocale(const QString &localeName, QObject *parent = 0);
    MLocale(const MLocale &other, QObject *parent = 0);

    virtual ~MLocale();

    MLocale &operator=(const MLocale &other);


    /*!
     * \brief Sets the default locale.
     */
    static void setDefault(const MLocale &locale);

    /*!
     * \brief Returns true if MLocale is valid and can be used
     */
    bool isValid() const;

    /*!
     * \brief Sets category with specified locale string
     * \param localeName ICU format locale ID string.
     */
    void setCategoryLocale(Category category, const QString &localeName);

    /*!
     * \brief Sets the collation mode
     */
    void setCollation(Collation collation);

    /*!
     * \brief Returns the collation mode
     */
    Collation collation() const;

    /*!
     * \brief Sets calendar type
     */
    void setCalendarType(CalendarType calendar);

    /*!
     * \brief Returns calendar type
     */
    CalendarType calendarType() const;

    /*!
     * \brief Returns a MCollator which compares QStrings based on language/country/collation rules
     */
    MCollator collator() const;

    /*!
     * \brief Returns the endonym of the language of the locale
     *
     * The language <a href="http://en.wikipedia.org/wiki/Endonym">endonym</a> is the
     * name of the language which is used by the native speakers of
     * this language.
     *
     * <table border="1">
     * <caption>
     *  <big><b>Examples for language endonyms</b></big>
     * </caption>
     * <tr>
     *    <th>English exonym</th><th>Language endonym</th>
     * </tr>
     * <tr>
     *    <td>German</td><td>Deutsch</td>
     * </tr>
     * <tr>
     *    <td>Russian</td><td>русский язык</td>
     * </tr>
     * <tr>
     *    <td>Japanese</td><td>日本語</td>
     * </tr>
     * </table>
     *
     */
    QString languageEndonym() const;

    /*!
     * \brief Returns the endonym of the country of the locale
     *
     * The country <a href="http://en.wikipedia.org/wiki/Endonym">endonym</a>
     * is the name of the country which is used by the inhabitants of that country.
     *
     * <table border="1">
     * <caption>
     *  <big><b>Examples for country endonyms</b></big>
     * </caption>
     * <tr>
     *    <th>English exonym</th><th>Language endonym</th>
     * </tr>
     * <tr>
     *    <td>Germany</td><td>Deutschland</td>
     * </tr>
     * <tr>
     *    <td>Russia</td><td>Россия</td>
     * </tr>
     * <tr>
     *    <td>Japan</td><td>日本</td>
     * </tr>
     * </table>
     *
     */
    QString countryEndonym() const;

    /*!
     * \brief Returns the language code of the locale in ISO-639 format
     */
    QString language() const;

    /*!
     * \brief Returns the country code of the locale in ISO-3166 format
     */
    QString country() const;

    /*!
     * \brief Returns the script code of the locale in ISO-15924 format
     */
    QString script() const;

    /*!
     * \brief Returns the variant appended to the locale
     */
    QString variant() const;

    /*!
     * \brief Returns the string representation of the locale
     */
    QString name() const;

    /*!
     * \brief Returns the text direction of the locale
     */
    Qt::LayoutDirection textDirection() const;

    /*!
     * \brief Returns the language code of the category in ISO-639 format
     */
    QString categoryLanguage(Category category) const;

    /*!
     * \brief Returns the country code of the category in ISO-3166 format
     */
    QString categoryCountry(Category category) const;

    /*!
     * \brief Returns the variant code appended to the category
     */
    QString categoryVariant(Category category) const;

    /*!
     * \brief Returns the string representation of the category
     */
    QString categoryName(Category category) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     *
     * \sa formatNumber(short i) const
     * \sa formatNumber(int i) const
     * \sa formatNumber(float i) const
     * \sa formatNumber(double i, int precision) const
     */
    QString formatNumber(qlonglong i) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     *
     * \sa formatNumber(qlonglong i) const
     * \sa formatNumber(int i) const
     * \sa formatNumber(double i, int precision) const
     * \sa formatNumber(float i) const
     */
    QString formatNumber(short i) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     *
     * \sa formatNumber(qlonglong i) const
     * \sa formatNumber(short i) const
     * \sa formatNumber(double i, int precision) const
     * \sa formatNumber(float i) const
     */
    QString formatNumber(int i) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     * \param precision number of fractional digits
     *
     * \sa formatNumber(qlonglong i) const
     * \sa formatNumber(short i) const
     * \sa formatNumber(int i) const
     * \sa formatNumber(float i) const
     */
    QString formatNumber(double i, int precision = -1) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     *
     * Examples:
     *
     * \code
     * // format a number to a string according to the conventions of the
     * // current system default locale:
     * MLocale locale;  // gets the current system default locale
     * QString numberString = locale.formatNumber(12345670.89);
     * \endcode
     *
     * \code
     * // format a number to a string using US English conventions no
     * // matter what the current system default locale is:
     * MLocale locale("en_US");
     * QString numberString = locale.formatNumber(12345670.89);
     * // now numberString contains “12,345,670.89”
     * \endcode
     *
     * \code
     * // format a number to a string using Arabic conventions no
     * // matter what the current system default locale is:
     * MLocale locale("ar");
     * QString numberString = locale.formatNumber(12345670.89);
     * // now numberString contains: “١٢٬٣٤٥٬٦٧٠٫٨٩”
     * \endcode
     *
     * \sa formatNumber(qlonglong i) const
     * \sa formatNumber(short i) const
     * \sa formatNumber(int i) const
     * \sa formatNumber(double i, int precision) const
     */
    QString formatNumber(float i) const;

    /*!
     * \brief Returns the string representation of a number as percentage
     * \param i number to format
     * \param decimals number of digits shown after decimal separator
     */
    QString formatPercent(double i, int decimals = 0) const;

    /*!
     * \brief Formats an amount of currency
     * \param amount amount to format
     * \param currency three letter currency code in ISO-4217 format, e.g. EUR or USD
     */
    QString formatCurrency(double amount, const QString &currency) const;

    /*!
     * \brief Creates a string presentation for a date time with explicit format lengths
     * \param dateTime time object to create representation from
     * \param dateType style of date formatting
     * \param timeType style of time formatting
     * \param calendarType calendar type to use for formatting
     *
     * If dateType is MLocale::DateNone <b>and</b> timeType is MLocale::TimeNone,
     * an empty string is returned.
     */
    QString formatDateTime(const QDateTime &dateTime, DateType dateType = DateLong,
                           TimeType timeType = TimeLong,
                           CalendarType calendarType = DefaultCalendar) const;

    /*!
     * \brief String presentation with explicit calendar type
     * \param dateTime time to format
     * \param calendarType calendar to use
     */
    QString formatDateTime(const QDateTime &dateTime, CalendarType calendarType) const;

    /*!
     * \brief Formats MCalendar using its native calendar system
     * \param mCalendar Calendar holding the datetime to format
     * \param datetype format for date
     * \param timetype format for time
     *
     * If dateType is MLocale::DateNone <b>and</b> timeType is MLocale::TimeNone,
     * an empty string is returned.
     */
    QString formatDateTime(const MCalendar &mCalendar, DateType datetype = DateLong,
                           TimeType timetype = TimeLong) const;

    QString formatDateTimeICU(const QDateTime &dateTime,
                              const QString &formatString) const;
    QString formatDateTimeICU(const MCalendar &mCalendar,
                              const QString &formatString) const;
    /*!
     * \brief creates a string presentation for a QDateTime with specific format string
     * \param dateTime QDateTime to format
     * \param formatString in ISO-14652 date time format
     *
     * \sa formatDateTime(const MCalendar &mCalendar, const QString &formatString) const
     */
    QString formatDateTime(const QDateTime &dateTime,
                           const QString &formatString) const;
    // divergence: not implemented modified field descriptors (%Ec, %EC, %EY etc)

    /**
    \brief Formats a date string based on ISO-14652 (draft) pattern

    \sa formatDateTime(const QDateTime &dateTime, const QString &formatString) const;

    For more information about the format characters used here see
    <a href="http://www.open-std.org/jtc1/SC22/WG20/docs/n972-14652ft.pdf">
    ISO-14652 (draft)
    </a>
    or
    <a href="http://linux.die.net/man/1/date">
    the man page of “date”
    </a>
    or
    <a href="http://www.gnu.org/s/libc/manual/html_node/Formatting-Calendar-Time.html">
    the documentation of the glibc function “strftime”
    </a>.

    The pattern may contain the following symbols to be replaced with
    the corresponding information:
     - \%a FDCC-set's abbreviated weekday name.
     - \%A FDCC-set's full weekday name.
     - \%b FDCC-set's abbreviated month name.
     - \%B FDCC-set's full month name.
     - \%c FDCC-set's appropriate date and time representation.
     - \%C Century (a year divided by 100 and truncated to integer) as decimal number (00-99).
     - \%d Day of the month as a decimal number (01-31).
     - \%D Date in the format mm/dd/yy.
     - \%e Day of the month as a decimal number (1-31 in at two-digit field with leading &lt;space&gt; fill).
     - \%F The date in the format YYYY-MM-DD (An ISO 8601 format).
     - \%g Week-based year within century, as a decimal number (00-99).
     - \%G Week-based year with century, as a decimal number (for example 1997).
     - \%h A synonym for %b.
     - \%H Hour (24-hour clock), as a decimal number (00-23).
     - \%I Hour (12-hour clock), as a decimal number (01-12).
     - \%j Day of the year, as a decimal number (001-366).
     - \%m Month, as a decimal number (01-13).
     - \%M Minute, as a decimal number (00-59).
     - \%n A &lt;newline&gt; character.
     - \%p FDCC-set's equivalent of either AM or PM.
     - \%r locale specific 12-hour clock time using the AM/PM notation
           Similar to “%I:%M %p” but the exact format does depend more on
           the locale. E.g. for “en_GB” locale the result may look like
           “12:15 PM” with a colon between the hours and he minutes whereas
           for “fi_FI” locale a dot may be used as the separator, like
           “12.15 ip.”. The exact result depends on how the TimeShort format
           for the locale is implemented in ICU.
     - \%R locale specific 24-hour clock time.
           Similar to “%H:%M” but the exact format depends on the locale.
           E.g. for “en_GB” locale the result may look like “14:15” and
           for “fi_FI” locale the result may look like “14.15”.
           The exact result depends on how the TimeShort format
           for the locale is implemented in ICU.
     - \%S Seconds, as a decimal number (00-61).
     - \%t A &lt;tab&gt; character.
     - \%T 24-hour clock time, in the format HH:MM:SS.
     - \%u Weekday, as a decimal number (1(Monday)-7).
     - \%U Week number of the year (Sunday as the first day of the week) as a
       decimal number (00-53). All days in a new year preceding the first
       Sunday are considered to be in week 0.
     - \%v Same as \%V, for compatibility
     - \%V Week of the year (Monday as the first day of the week), as a decimal
       number (01-53). The method for determining the week number is as
       specified by ISO 8601.
     - \%w Weekday, as a decimal number (0(Sunday)-6).
     - \%W Week number of the year (Monday as the first day of the week), as a
       decimal number (00-53). All days in a new year preceding the first
       Monday are considered to be in week 0.
     - \%x FDCC-set's appropriate date representation.
     - \%X FDCC-set's appropriate time representation.
     - \%y Year within century (00-99).
     - \%Y Year with century, as a decimal number.
     - \%z The offset from UTC in the ISO 8601 format "-0430" (meaning 4 hours
       30 minutes behind UTC, west of Greenwich), or by no characters if no
       time zone is determinable.
     - \%Z Time-zone name, or no characters if no time zone is determinable.
     - \%% A &lt;percent-sign&gt; character.
    */
    QString formatDateTime(const MCalendar &mCalendar,
                           const QString &formatString) const;

    /*!
     * \brief Formats a phone number according to the given grouping
     */
    QString formatPhoneNumber( const QString& phoneNumber,
			       PhoneNumberGrouping grouping =
			       DefaultGrouping ) const;

    /*!
     * \brief returns ICU date and time format string of the current locale
     * \param dateType style of date formatting
     * \param timeType style of time formatting
     * \param calendarType calendar to use for formatting
     */
    QString icuFormatString( DateType dateType = DateLong,
                              TimeType timeType = TimeLong,
                              CalendarType calendarType = DefaultCalendar) const;

    /*!
     * \brief Creates a datetime object from a string with explicit format lengths.
     * \param dateTime string to parse
     * \param dateType style of date formatting
     * \param timeType style of time formatting
     * \param calendarType calendar to use for formatting
     *
     * If dateType is MLocale::DateNone <b>and</b> timeType is MLocale::TimeNone,
     * an invalid QDateTime is returned.
     */
    QDateTime parseDateTime(const QString &dateTime, DateType dateType = DateLong,
                            TimeType timeType = TimeLong,
                            CalendarType calendarType = DefaultCalendar) const;

    /*!
     * \brief Creates a datetime object from a string with explicit calendar type.
     * \param dateTime string to parse
     * \param calendarType calendar to use
     */
    QDateTime parseDateTime(const QString &dateTime, CalendarType calendarType) const;

    /*!
     * \brief Returns the locale dependant name for a month number
     */
    QString monthName(const MCalendar &mCalendar, int monthNumber) const;

    /*!
     * \brief Returns the locale dependant name for a month using context information
     */
    QString monthName(const MCalendar &mCalendar, int monthNumber,
                      DateSymbolContext context, DateSymbolLength symbolLength) const;

    /*!
     * \brief Returns locale dependant weekday name
     */
    QString weekdayName(const MCalendar &mCalendar, int weekday) const;


    /*!
     * \brief Returns locale dependant weekday name using context information
     */
    QString weekdayName(const MCalendar &mCalendar, int weekday,
                        DateSymbolContext context, DateSymbolLength symbolLength) const;

    // TODO: add versions for QDate and QTime?

    ////////////////////////////////
    //// ID translation scheme /////

    /*!
     * \brief Copies translations from another MLocale
     * the catalogs are reloaded based on the locale settings
     */
    void copyCatalogsFrom(const MLocale &other);

    /*!
     * \brief installs a translation catalog
     * \param name of the translation catalog to install
     *
     * Adds this translation catalog to the list of translation catalogs
     * used by this MLocale.
     *
     * The list of catalogs used by the system default locale is the
     * list of catalogs which will be used when translating strings
     * with qtTrId() or tr().
     *
     * Usually the catalog name should be specified <b>without</b> the
     * “.qm” file extension and <b>without</b> the locale specific
     * part of the file name. I.e. one should usually call
     * installTrCatalog("foo") and <b>not</b>
     * installTrCatalog("foo_en_US.qm").
     *
     * If only the basename of the catalog (e.g. "foo") is specified,
     * installTrCatalog() installs both the engineering
     * English file for this catalog <b>and</b> the real translations
     * for this catalog for the locale. The engineering English
     * gets lowest priority by prepending it to the list of
     * already installed catalogs and the real translations get
     * highest priority by appending it to the list of already
     * installed catalog names.
     *
     * Example:
     *
     * Add translation catalogs “foo” and “bar” to the catalogs used
     * by the system default locale:
     *
     * \code
     * // get current system default locale
     * MLocale locale;
     * // install a translation catalog
     * // (this catalog is added to the list of catalogs already used
     * // by the system default locale):
     * locale.installTrCatalog("foo");
     * locale.installTrCatalog("bar");
     * // make the locale with the added translation catalog the new system
     * // default:
     * MLocale::setDefault(locale);
     * \endcode
     *
     * In this example, after calling locale.installTrCatalog("foo") the
     * internal list of installed catalog names of the locale looks like:
     *
     * \code
     *    "foo.qm" "bar.qm" ... previous catalog list ... "foo" "bar"
     * \endcode
     *
     * Priority in this list increases from left to right.
     *
     * Eventually, this list of catalog names is evaluated and
     * translation files are loaded from the file system.
     * The translation files are searched in the directories
     * in the translation path list, see translationPaths().
     *
     * For entries in the list of catalog names which end with “.qm”
     * the names are used “as is”, i.e. in the example above the files
     * “foo.qm” and “bar.qm” are loaded for these entries. For entries
     * in the list of catalog names which do <b>not</b> end with
     * “.qm”, a locale specific file name part and a “.qm” extension
     * is added and Qt-like fallbacks for the file name to load are
     * used.  As an example, let’s assume that the name of the locale
     * is “en_US”, then the following file names are tried to get
     * the real translations for the catalog name “foo”:
     *
     * \code
     * foo_en_US.qm
     * foo_en_US
     * foo_en.qm
     * foo_en
     * \endcode
     *
     * and the first one which exists is loaded.
     *
     * Note that the search for fallbacks for the real translation
     * stops at “foo_en”. This is slightly different from the
     * behaviour of <a
     * href="http://qt.nokia.com/doc/4.6/qtranslator.html#load">QTranslator::load()</a>
     * because proceeding to the fallback “foo.qm” would load
     * engineering English if “foo.qm” exists which is not what we
     * want when trying to load real translations because this might
     * add engineering English with the wrong priority (highest
     * priority) to the list of translation catalogs if the real
     * translation happens to be missing.
     *
     * If the settings of the locale change, the list of translation
     * catalog names is reevaluated and translations may switch to
     * a different language (see connectSettings(), disconnectSettings(),
     * settingsChanged(), localeSettingsChanged()).
     *
     * If a full file name including a “.qm” extension is specified
     * as the argument of installTrCatalog(), this catalog name is
     * always appended to the list of catalog names, i.e. used with
     * highest priority. This means that after calling
     * locale.installTrCatalog("foo_en_US.qm") the internal list
     * of installed catalog names looks like:
     *
     * \code
     *    ... previous catalog list ... "foo_en_US.qm"
     * \endcode
     *
     * This is mainly intended for testing to force loading of a fully
     * specified translation file with highest priority. Except
     * for testing this should not be used because in the above example
     * with “foo_en_US.qm”, the locale specific part does not change
     * according to the locale settings but always stays like this.
     * And loading an engineering English file by specifying
     * the full file name, i.e. installTrCatalog("foo.qm") should
     * also be used only for testing because this adds the engineering
     * English with highest priority which is usually wrong.
     *
     * After a locale has been made the system default with setDefault(),
     * the translation catalogs which have been installed into that locale
     * are available for use with qtTrId(), i.e. one can use code
     * like this to translate a string:
     *
     * \code
     * // translate a string:
     *
     * //% "Hello"
     * QString translatedString = qtTrId("hello_msg");
     * \endcode
     *
     * \sa setDefault(const MLocale &locale)
     * \sa translationPaths()
     * \sa setTranslationPaths(const QStringList &paths)
     * \sa addTranslationPath(const QString &path)
     * \sa removeTranslationPath(const QString &path)
     */
    void installTrCatalog(const QString &name);

    /*!
     * \brief removes a translation catalog
     * \param name of the translation catalog to remove
     *
     * Removes the catalog from the list of translation catalogs used by this
     * MLocale.
     */
    void removeTrCatalog(const QString &name);

    /*!
     * \brief tr() compatibility translation method.
     * \param context context of the translation
     * \param sourceText text to translate
     * \param comment about the translation. may be helpful when creating translation files
     * \param n plurality
     */
    QString translate(const char *context, const char *sourceText,
                      const char *comment = 0, int n = -1);

    /*!
     * \brief Sets the DataPaths for the (ICU) locale system to the given paths.
     *
     * \param dataPaths a list of paths
     *
     * This should be called at most once in a process before creating
     * any MLocale instances. This function is not thread-safe.
     * Use it before doing anything with MLocale instances from multiple
     * threads.
     *
     * This function calls u_setDataDirectory() in libicu, see also
     * <a href="http://icu-project.org/apiref/icu4c/putil_8h.html">
     * http://icu-project.org/apiref/icu4c/putil_8h.html</a>.
     *
     * libmeegotouch initialises this data path to the value of the macro
     *
     * \code
     *     M_ICUEXTRADATA_DIR
     * \endcode
     *
     * which is normally set to
     *
     * \code
     *     /usr/share/meegotouch/icu/
     * \endcode
     *
     * usually one should not change this.
     *
     * The user data itself should be in the ICU specific
     * subdirectories at the given paths, e.g. a user override file
     * for some of the basic data of the Finnish locale should be
     * in
     *
     * \code
     *     /usr/share/meegotouch/icu/usrdt42l/fi.res
     * \endcode
     *
     * and a user override file for the lang data of the Finnish
     * locale should be in
     *
     * \code
     *     /usr/share/meegotouch/icu/usrdt42l/lang/fi.res
     * \endcode
     *
     * etc.
     *
     * \sa void setDataPath(const QString &dataPath)
     */
    static void setDataPaths(const QStringList &dataPaths);

    /*!
     * \brief Sets the DatPaths to given path
     *
     * \param dataPath the data path
     *
     * convenience function to set the data path to a single directory
     *
     * \sa setDataPaths(const QStringList &dataPaths)
     */
    static void setDataPath(const QString &dataPath);

    /*!
     * \brief Sets the paths that are used as base directories for using translations
     * The translation path modification methods are not thread-safe.
     *
     * \sa  translationPaths()
     * \sa addTranslationPath(const QString &path)
     * \sa removeTranslationPath(const QString &path)
     */
    static void setTranslationPaths(const QStringList &paths);

    /*!
     * \brief Append a path to the translation file lookup directories.
     *
     * \sa translationPaths()
     * \sa setTranslationPaths(const QStringList &paths)
     * \sa removeTranslationPath(const QString &path)
     */
    static void addTranslationPath(const QString &path);

    /*!
     * \brief Removes a path
     *
     * \sa translationPaths()
     * \sa setTranslationPaths(const QStringList &paths)
     * \sa addTranslationPath(const QString &path)
     */
    static void removeTranslationPath(const QString &path);

    /*!
     * \brief Returns the list of current translation file base paths
     *
     * \sa setTranslationPaths(const QStringList &paths)
     * \sa addTranslationPath(const QString &path)
     * \sa removeTranslationPath(const QString &path)
     */
    static QStringList translationPaths();

    /*!
     * \brief Monitors all changes in the locale related gconf keys
     *
     * After calling this method, all changes in the locale related
     * gconf keys will change this locale according to the changes in the
     * gconf keys, set this locale as the new system default locale
     * and emit the settingsChanged() signal.
     */
    void connectSettings();

    /*!
     * \brief Disconnects from change monitoring in settings
     * After calling this method, all changes in the settings
     * will no longer emit settingsChanged() signal
     */
    void disconnectSettings();

Q_SIGNALS:
    void settingsChanged();
    /*!
     * \brief Signal emitted when the default system locale changes.
     */
    void localeSettingsChanged();

protected:

    /*!
     * \brief Returns the default locale object.
     */
    static MLocale &getDefault();

private:
    // not implemented now
    bool operator==(const MLocale &other) const;
    bool operator!=(const MLocale &other) const;

    // global default locale
    static MLocale *s_systemDefault;

    // private info is kept away from the public header
    MLocalePrivate *const d_ptr;
    Q_DECLARE_PRIVATE(MLocale)

    friend class MCalendar;
    friend class MCollator;
    friend class MIcuBreakIteratorPrivate;

private Q_SLOTS:
    void refreshSettings();
};

#endif
